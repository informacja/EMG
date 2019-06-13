#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "kissfft-131/kiss_fft.c"
// samo .h nie bangla, uzasadnienie poniżej
//Kissfft is not really something you need to make and install like other libraries. If you need complex ffts,
//then all you need to do is compile the kiss_fft.c in your project. If you need something more specialized
//like multidimensional or real ffts, then you should also compile the apropriate file(s) from the tools dir.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime myTimer; myTimer.start();

    ui->setupUi(this);

    qDebug() << "setupUi:" <<myTimer.elapsed() << "ms"; myTimer.start();

    connect(&thread, SIGNAL(tick()), this, SLOT(externalThread_tick()));
    connect(ui->actionRun,  SIGNAL(triggered()), this, SLOT(sendCommand()));
    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->actionBar,  SIGNAL(triggered()), this, SLOT(update()));
    connect(this, SIGNAL(simulation_changed()), this, SLOT( set_simulation() ));

//    Counter a, b;
//    QObject::connect(&a, SIGNAL(valueChanged(int)),
//                     this, SLOT(say_hello() ));

//      a.setValue(12);  // a.value() == 12, b.value() == 12

//      qDebug() << b.value();
//    connect(this->simulation, SIGNAL(simulation_changed(Simulation_Type)), this->simulation, SLOT(simulationSet(const Simulation_Type& )));
//    connect(slider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged(int)));

                timeDataCh1.resize(DSIZE2);
    //            timeDataCh2.resize(DSIZE2);
    //            timeDataCh3.resize(DSIZE2);
    //            timeDataCh1.fill(0);
    //            timeDataCh2.fill(0);
    //            timeDataCh3.fill(0);

    ui->statusBar->showMessage("No device");
//    simulation = SIMULATION_STOP;                    // default: find source
    set_simulation( SIMULATION_STOP );

    QString portname;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if(info.serialNumber()=="NXP-77")
        {
            portname=info.portName();
            serial.setPortName(portname);
            if (serial.open(QIODevice::ReadWrite))
            {
//                serial.setBaudRate( serial.Baud115200,  serial.AllDirections);
                ui->statusBar->showMessage(tr("Device: %1").arg(info.serialNumber()));
                serial.clear();
                simulation = SIMUL_REALTIME;
//                thread.start(thread.HighestPriority);     // zawsze startuj wątek, przeniesione poniżej
            }
            else {

                ui->statusBar->showMessage(tr("Can't open %1, error code %2") .arg(serial.portName()).arg(serial.error()));
                return;
            }
            break;
        }
    }

    chart.gridNumX=10;
    chart.gridNumY=10;
    chart.minValueX= 1;
    chart.maxValueX= DSIZE2;
    chart.minValueY= 0;
    chart.maxValueY= 1;
    chart.chartMode=LinearChart;
    chart.dataSize=DSIZE2;

    alloc_memory_sub_constructor();
    pointers_set_null();
    alloc_files();

    isinverse = 0;          // for fft

    for (int i = 0; i < DSIZE2; i++)
    {
       hamming[i] = static_cast<float>( (0.54-((0.46) * cos(2*M_PI*i/(DSIZE2-1)))) );
       hann[i]    = static_cast<float>( 0.5 * (1 - cos(2*M_PI*i/DSIZE2)) );
    }

    setAcceptDrops(true);

    // Output WAVE settings
    format.setCodec("audio/pcm");
    format.setSampleRate(DSIZE2);                           // Hz sample per second
    format.setChannelCount(1);                              // NCH
    format.setSampleSize(sizeof(timeData[0][0])*2);         // sizeof(double)*2
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SampleType::Float); // nie ma double co zrobić?

    int i = 0;
    file_out.setFileName( FILE_NAME EXT );
    while(file_out.exists())
      {
        if( file_out.size() == 0 )  // jeśli plik pusty, to nadpisz
          break;
        i++;
        file_out.setFileName( FILE_NAME + QVariant(i).toString() + EXT );
      }

    file_csv.setFileName( FILE_NAME ".csv");


//    qDebug() << "File exist?" << QFile::exists(wav_path) << wav_path;


    /* zasady:
     * jeśli jest plik ini to wczytaj ustawienia
      szukaj pliku wejścia w katalogu

    */


//    jeśli realtime
//       otwieraj wszystkie pliki zapisuj do domyślnego
//    else czytaj z jednego źródła

    QString input_file = "../DataTransfer_PWM/2.wav"; //temp

    if( !QCoreApplication::arguments().contains("-nosettings",Qt::CaseSensitivity::CaseInsensitive) )
        if( !serial.isOpen() )
            input_file = loadSettings().toString();     // ścieżka do pliku z zapisu EMG


    qDebug() << "Symulacja?" << simulation;

    if( simulation == SIMULATION_STOP )
        simulation = find_source_file(input_file);

    switch(simulation) // teoretycznie do usunięcia
    {
        case SIMUL_REALTIME:     // nawiązano połączenie z płytką
            file_out.open(QIODevice::WriteOnly | QIODevice::Append);    // bin
            qDebug() << "Plik do zapisu" << wav_out->open(FILE_NAME EXT, format);
          break;
        case SIMULATION_CSV:    break;
        case SIMULATION_WAV:
        {
            // get first file in directory
        //            QString wav_path = "../DataTransfer_PWM/2.wav"; //temp

//            if(!QFile::exists(wav_path)) {
//                ui->statusBar->showMessage("Nie istnieje plik " + wav_path);
//                simulation = SIMULATION_STOP;
//                break;
//            }

            if( !wav_in->open(input_file) ) // WAV have valid header
            {
                ui->statusBar->showMessage("Niepoprawny plik WAV: "+input_file);
                simulation =SIMULATION_STOP;
            }
            else {
                ui->statusBar->showMessage(input_file);
            }
            break;
        }
        case SIMULATION_BINARY: break;      /* deprecated */
        case SIMULATION_STOP:
            // szukaj plików do otwarcia
        break;
//    default: break;
    }

    file_csv.open(QIODevice::Append);
    stream.setDevice( (QIODevice*) &file_csv );

//    ui->textEdit->setVisible(ui->actionSave->isChecked());
    ui->textEdit->setText( file_out.fileName() );

//#ifdef QT_DEBUG
//    ui->selectInput2->setChecked(false);
    ui->selectInput3->setChecked(false);
//#endif //QT_DEBUG

//    QSplitter *splitter = new QSplitter(this);

//    QFileSystemModel *model = new QFileSystemModel;
//       model->setRootPath(QDir::currentPath());
//       QTreeView *tree = new QTreeView(splitter);
//       tree->setModel(model);
////       QListView *listview = new QListView;
//         QTreeView *treeview = new QTreeView;
//         QTextEdit *textedit = new QTextEdit;

//         splitter->resize(300,200);
//         splitter->move( 0 , 150);
//         tree->setVisible(false);
//         splitter->setChildrenCollapsible(true);


//         splitter->
//         tree->resize(100,100);//setWindowwidth(100);

//         splitter->addWidget(listview);
//         splitter->addWidget(treeview);
//         splitter->addWidget(textedit);
//       QList a(3,2);

//       splitter->setSizes()


//    qDebug() << "Format isvalid: " << format.isValid();

         //TODO
//         QMimeDatabase db;
//         QMimeType mime = db.mimeTypeForFile("../.", QMimeDatabase::MatchContent);
//         qDebug() << mime.name();            // Name of the MIME type ("audio/mpeg").
//         qDebug() << mime.suffixes();        // Known suffixes for this MIME type ("mp3", "mpga").
//         qDebug() << mime.preferredSuffix(); // Preferred suffix for this MIME type ("mp3").


    thread.start(thread.HighestPriority);

    int nMilliseconds = myTimer.elapsed();
    qDebug() << "Constructor elapsed time:" << nMilliseconds << "ms";
}

// -----------------------------------------------------------------------------
void MainWindow::alloc_memory_sub_constructor()
{
    timeData.resize(NCH);
    spectrum.resize(NCH);
    for(int i=0; i< timeData.size();i++)        // dla wszystkich kanalow
    {
        timeData[i].resize(DSIZE2);
        timeData[i].fill(0);
        spectrum[i].resize(DSIZE2);
        spectrum[i].fill(0);
    }

    meanData.resize(NCH);
    meanData.fill(0.0);

    // Added
    cfg = kiss_fft_alloc( DSIZE2, isinverse, nullptr, nullptr );
    if(cfg == nullptr){
        ui->statusBar->showMessage(tr("Can't alloc cfg in MainWindow(QWidget *parent) "));
        return;
    }

    for (int i = 0; i < NCH; i++)
    {
        in[i]=static_cast<kiss_fft_cpx*>(KISS_FFT_MALLOC(DSIZE2*sizeof(*in[0])));
        out[i]=static_cast<kiss_fft_cpx*>(KISS_FFT_MALLOC(DSIZE2*sizeof(*out[0])));
        if(in[i] == nullptr){
            ui->statusBar->showMessage(tr("Can't alloc in[%d] in MainWindow(QWidget *parent) "),i);
            return;
        }
        if(out[i] == nullptr){
            ui->statusBar->showMessage(tr("Can't alloc out[%d] in MainWindow(QWidget *parent) "), i);
            return;
        }
        memset(in[i],0,DSIZE2  * sizeof(*in[0]));
        memset(out[i],0,DSIZE2 * sizeof(*out[0]));
    }

    hamming = static_cast<kiss_fft_scalar*>( KISS_FFT_MALLOC(DSIZE2*sizeof(hamming[0])) );
    hann    = static_cast<kiss_fft_scalar*>( KISS_FFT_MALLOC(DSIZE2*sizeof(hann[0])) );
    if (hamming == nullptr) {
        ui->statusBar->showMessage(tr("Can't alloc hamming in MainWindow(QWidget *parent) "));
        return;
    }
    if (hann == nullptr) {
        ui->statusBar->showMessage(tr("Can't alloc hann in MainWindow(QWidget *parent) "));
        return;
    }
}

void MainWindow::pointers_set_null()
{
    wav_out = nullptr;
    wav_in  = nullptr;
}
void MainWindow::alloc_files()
{
  wav_in = new WavFilerReader(nullptr);
  wav_out = new WaveFileWriter(nullptr);
}

MainWindow::~MainWindow()
{    
    wav_in->close();
    wav_out->close();

    thread.terminate();
    thread.wait();
    serial.close();

//    if(wav_in->isOpen()) wav_in->close();
//    if(file_out.isOpen()) file_out.close();
    if(file_csv.isOpen()) file_csv.close();
    for (int i = 0; i < NCH; i++)
    {
        free(in[i]);
        free(out[i]);
    }
    kiss_fft_free(cfg);

//Qlistv

//    delete file_csv;
//    delete file_out;
    delete [] hamming, hann;
    delete wav_in;
    delete wav_out;
    delete ui;
}

//-----------------------------------------------------------------------------
// Public slots
//-----------------------------------------------------------------------------

// =============================================================================
/* ToDo:
 * spektrum / 2 => 512 Hz
 *
 *
 *
   Emulowanie wejścia np. odtwarzanie nagrania
   szumy, typu piła, wygasające
 * rysowanie widma 2 pola
 * RMS -
 * Github kody publikacja - does't allowed
    zapis i odczyt
    lista plikow
    wczytywanie wav- zwracanie rozmiaru zamiast bool


 * //assume the directory exists and contains some files and you want all jpg and JPG files
QDir directory("Pictures/MyPictures");
QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
foreach(QString filename, images) {
//do whatever you need to do

// waw header
// i data descripto r do zmiany później
}

//        20*log10(sqrt(x)) we can just do 10*log10(x)
//           window[ctr] = hamming[ctr]*y[ctr];

// furier         do 1KHz   probowanie do 45
// port 1-wszy pod 11
QIamge
Qpixmap

 */
//double rms(double x[], int n)
double rms(double* x, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += pow(x[i], 2);

    return sqrt(sum / n);
}

void MainWindow::externalThread_tick()
{
    if( simulation != SIMULATION_STOP )
        auto_actionRun_serial_port(3);                                             // automatyczny start rysowania po ekranie
    else {
      ui->statusBar->showMessage("Przenieś i upuść na program plik typu (WAV, CSV) drag&drop SIMULATION_STOP",1000);
      ui->actionRun->setChecked(false);
    }

  if(ui->actionRun->isChecked())
//    if( buff.size() > 0)                                                        // serial port lub z pliku
    {
//    qDebug() << "simulation:  " <<simulation;

      if(buff.size() == 0)
      {
        if (!load_data()){
           qDebug() << "load data";
          return;
        }
      }
        uint16_t* sample = reinterpret_cast<uint16_t*>(readdata.data());
        if (simulation == SIMULATION_WAV)
        {
            static size_t krok;
            sample = reinterpret_cast<uint16_t*>(buff.data());
            krok += DSIZE;
            sample += krok;
              qDebug() <<"krok:" <<  krok<< krok+NCH*DSIZE2;
            ui->statusBar->showMessage(QString::number(krok));
//            QThread::msleep(1);
            if( krok >= buff.size()-DSIZE)
            {
                qDebug() <<"exit at krok:" <<  krok  ;
              ui->actionRun->setChecked(false);
              buff.clear();
              buff.resize(0);
              krok = 0;
              simulation=SIMULATION_STOP;
              return;
            }
        }
        for(int i=0; i<DSIZE2; i++)
        {
            for(int k=0; k<NCH; k++)
            {
                timeData[k][i]=(*sample++)/65535.0;
                (in[k]+i)->i = 0;

                if(ui->radioBtn_rect->isChecked())
                {
                    (in[k]+i)->r = timeData[k][i];//(*sample)/65535.0;
                    //do nothing
                }
                else if (ui->radioBtn_hann->isChecked()) {
                     (in[k]+i)->r = timeData[k][i] * hann[i];//(*sample)/65535.0;
                }
qDebug() <<"2"   ;
//                float freq =200; test[i].r = sin(2 * M_PI * freq * i / DSIZE2), test[i].i = 0;  test[i].i = 0; test[i].r = kiss_fft_scalar (*sample)/65535.0;
//                if(ui->pwmValue1->value())
//                    (in[k]+i)->r *=  ( hamming[i] + ui->pwmValue1->value()/100 );    // TO DO Hamming window
            }
        }

        if( ui->actionSave->isChecked() )
            save_to_file( 0 );

        for (int k = 0; k < NCH; k++)
        {
            kiss_fft( cfg, in[k], out[k] );
           // kiss_fft( cfg, test, out[k] );

            for (int i = 1; i < DSIZE2/2; i++)
            {
//                if ( i >= DSIZE2 ) // na wypadek zwiękaszania pętli np. razy 2
//                {
//                    break;
//                }
                  double normBinMag = sqrt(SQUARE((out[k]+i)->r) + SQUARE((out[k]+i)->i))/51.2 ; // do konca nie wiem czemu tu musze mnozyc przec 8
//                   normBinMag = sqrt(SQUARE(test[i].r) + SQUARE(test[i].i))  ; // do konca nie wiem czemu tu musze mnozyc przec 8
                  double mag = normBinMag;

                  i *= 2;       // przedział zmiennej i: od 0 do 512 mnożony razy dwa

                  spectrum[k][i] = mag;            // TODO nie mieści się na wykresie//                  spectrum[k][i] = (out[0]+i)->r * hamming[i];
                  spectrum[k][i-1] = mag;            // TODO nie mieści się na wykresie//                  spectrum[k][i] = (out[0]+i)->r * hamming[i];

                  int a = 10;
                  if( a < i && i < DSIZE-a) // Hz
                  {
                    timeData[1][i] = rms(&spectrum[0][i-a],a*2);
                    timeData[1][i-1] = timeData[1][i];
                  }
                  else
                  {
                    timeData[1][i] = 0;
                    timeData[1][i-1] = 0;
                  }

//                   a = 20;
                  int n = DSIZE2 / a; // Hz (okno)

                  if( meanData.size() != n )
                    meanData.resize(n);

                  for(int j=0; j<n; j++) // słupki wypełniena
//                  if ( n > 0 && i % n == 0 )
                  {
              //            meanData[j] = std::accumulate( timeData[j].begin(), timeData[j].end(), 0.0)/timeData[j].size();
                      //                      meanData[i/n] = i/n;
                    meanData[j] = (double) j/n;
                  }

                  i /= 2;
//                  fprintf((FILE*) &file, "bin: %4d,   freq: %*.1f [Hz],   mag: %2.4f,   ampl.: %*f [dB]\n",
//                         (int)i*100, 12,44100*(double)i*100/(DSIZE2), normBinMag, 11, amplitude);

//                  char buffer [100];
//                  int n=sprintf (buffer, "bin: %4d,   freq: %*.1f [Hz],   mag: %2.4f,   ampl.: %*f [dB] %d %d",
//                                 (int)i, 12,1024*(double)i/(DSIZE2), normBinMag, 11, amplitude);
//                  if( i %100 == 0 )
//                    {
//                      qInfo() << buffer;
//                    if( i %500 == 0)
//                         qInfo() << endl;
//                    }
//                   qInfo() << amplitude << (out[k]+i)->r << (out[k]+i)->i;
             }
        }

        int d = DSIZE2/NBARS;

        if( meanData.size() != NBARS )
          meanData.resize(NBARS);

        ui->statusBar->showMessage( "Rozmiar d: " + QString::number(DSIZE2));

        for (int i = 0; i < NBARS; i++) {
//            meanData[i]=(double)i/d;
//             if( a < i && i < DSIZE2-a) // Hz
             meanData[i] = rms(&spectrum[0][(d)*i],d);
//            meanData[i]=rms(&spectrum[0][d*q],0);
        }

        update();

        if(ui->actionRun->isChecked())
          if (simulation == SIMUL_REALTIME)
            sendCommand();

        readdata.resize(0); // don't move, clear readdata only if was displayed

//        if(simulation)
    }
}

// -----------------------------------------------------------------------------

void MainWindow::sendCommand()
{
    senddata.clear();
    senddata[0]=static_cast<char>(128+(ui->actionTrigger->isChecked()<<6));
    senddata[1]=static_cast<char>(ui->pwmValue1->value());
    senddata[2]=static_cast<char>(ui->pwmValue2->value());
    senddata[3]=static_cast<char>(ui->pwmValue3->value());
    serial.write(senddata);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    chart.drawLinearGrid(painter, centralWidget()->geometry());

    if(ui->actionLine->isChecked())
    {
        if(ui->selectInput1->isChecked())
        {
//            for(int i = 0; i < timeData[0].size(); i++)
//                timeData[0][i] = (out[0]+i)->r * hamming[i];
            chart.plotColor=Qt::darkGray;

//            chart.drawLinearData(painter, (QVector<double>*)meanData);
//            chart.drawLinearData(painter, timeData[0]);
              chart.plotColor=Qt::red;
              chart.drawLinearData(painter, timeData[0]);

//              chart.plotColor=Qt::yellow;
//              chart.drawLinearData(painter, spectrum[0]);
        }
        if(ui->selectInput2->isChecked())
        {
            chart.plotColor=Qt::green;
            chart.drawLinearData(painter, timeData[1]);
        }

        if(ui->selectInput3->isChecked())
        {
            chart.plotColor=Qt::yellow;
            chart.drawLinearData(painter, timeData[2]);
        }
    }
    if( ui->actionSpektrum->isChecked())
    {
        chart.plotColor=Qt::gray;
        chart.drawLinearData(painter, spectrum[0]);
    }

    if(ui->actionBar->isChecked()) {
        chart.plotColor=Qt::cyan;
        chart.drawBarsData(painter, meanData);
    }

#ifdef FPS
    fps.paintEvent(event);
#endif
//printf("FPS is %f\n", m_frameCount / (float(m_timer.elapsed()) / 1000.0f));@
//    QThread::msleep(1);
}

// -----------------------------------------------------------------------------

inline void MainWindow::auto_actionRun_serial_port(int count_up_to)
{
    static int waiter(0);

    if( waiter >= 0 )
    {
     if(!ui->actionRun->isChecked())
     {
         if( waiter <= count_up_to ) {
             serial.clear();
             waiter++;
         }
         else {
             ui->actionRun->setChecked(true);
             ui->actionRun->triggered(true);
             waiter = -1;
         }
         QThread::msleep(10);
     }
    }
}

// -----------------------------------------------------------------------------

qint64 MainWindow::load_data(bool add_seconds)
{
    if(simulation)                                  // czytaj dane z pliku
    {
       return simulation_read_data_from_file();
    }
    else if( serial.size() >= DSIZE  )              // zapisz do pliku
    {
        readdata = serial.readAll();
        return readdata.size();
    }
    else
        return 0;
}

// -----------------------------------------------------------------------------

void MainWindow::save_to_file( bool add_seconds)
{
  for (int k = 0; k < 1/*NCH*/; k++)
  {
      if(add_seconds)
      {
//          stream << "[" << QDateTime::currentMSecsSinceEpoch() << "]" << readdata << endl;
          // no csv
//          file_out.write(( QString::toUtf8( QDateTime::currentMSecsSinceEpoch() ) ));
      }

//        file_out.write(reinterpret_cast<char*>(timeData[k].data()), static_cast<uint>(timeData[k].size())*sizeof(double));
        wav_out->write(reinterpret_cast<char*>(timeData[k].data()), static_cast<uint>(timeData[k].size())*sizeof(double));

        qInfo() <<"zapisano kanał "<<  k << ": " << timeData[k].size();
        for (int i = 0; i < timeData[0].size(); i++)
        {
            stream <<  timeData[k][i] << ",";    // out.csv
        }
//        qInfo() << file.fileName();
        stream << endl;

        // save WAV

   }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

// -----------------------------------------------------------------------------

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;

        if( simulation_open_file( fileName ) )
        {
            break; // don't proces more files in drag&drop
        }
    }
}

// -----------------------------------------------------------------------------

void MainWindow::on_textEdit_textChanged()
{
    ui->actionSave->setChecked(false);
}

void MainWindow::on_actionSave_triggered()
{
     ui->textEdit->setVisible(ui->actionSave->isChecked());
     if(ui->actionSave->isChecked() == true)
     {
         if(file_out.isOpen())
            file_out.close();
         file_out.setFileName(ui->textEdit->toPlainText());
         file_out.open(QIODevice::Append);
     }
}

// -----------------------------------------------------------------------------

void MainWindow::on_actionOpen_triggered()
{
    QDir start_dir = QCoreApplication::applicationDirPath(); // TODO: uper dir in tree
    start_dir.cdUp();

    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Otwórz plik danych"), start_dir.path(),
    tr("Binary, CSV, WAVE files (*.bin *.csv *.wav)\n"
       "Comma Separated Values (*.csv)\n"
       "WAVE audio file (*.wav)\n"
       "Binary Files (*.bin)\n"
       "Wszystkie pliki (*.*)"));

   simulation_open_file(fileName);
}

// -----------------------------------------------------------------------------

bool MainWindow::simulation_open_file( QString fileName ) // retrun? enum simulation?
{
  if(QFileInfo::exists(fileName) && QFileInfo(fileName).isFile())
  {
    QFileInfo fi(fileName); // to get extension suffix
    qDebug() << "Si_open_file" << fi.fileName() << "size:" << fi.size();
    ui->statusBar->showMessage( fileName );

    if ( fi.size() < DSIZE2 )
    {
      ui->statusBar->showMessage( "Plik jest mnijeszy od " + DSIZE2 + fileName );
      return false;
    }

    if(  fi.suffix() == "wav" ) {
      simulation = SIMULATION_WAV;
    }else if (fi.suffix() == "csv") {
      simulation = SIMULATION_CSV;
    }

    stream.resetStatus();
    switch (simulation)
    {
        case SIMULATION_WAV:
        {
          wav_in->close();                 // zamknij poprzedni plik

          wav_in->setFileName( fileName );
          wav_in->open(QIODevice::ReadOnly);

          qDebug() << "isOpen:" << wav_in->isOpen();
          if( !wav_in->isOpen() )
              return false;

        } break;
        case SIMULATION_CSV:
        {
          file_csv.close();

          file_csv.setFileName(fileName);
          file_csv.open(QIODevice::ReadOnly);

          stream.setDevice( static_cast<QIODevice*> (&file_csv) );
          if( !file_csv.isOpen() )
          {
              simulation = SIMULATION_STOP;
              QMessageBox msgBox;
              msgBox.setText("Nie udało się otworzyć pliku");
              msgBox.exec();
              return false;
          }
          break;
        }default: {
              ui->statusBar->showMessage("Nieznane rozszerzenie pliku: " + fi.fileName() );
              return false;
        }
    }

    // default if isOpen() for csv or wave
    ui->actionRun->setChecked(true);
    return true;
  }
  else return false;
}

// -----------------------------------------------------------------------------

void MainWindow::saveSettings( const QVariant &value, const QString &key, const QString &group)
{
  QSettings settings(QSettings::IniFormat, QSettings::SystemScope,
             QCoreApplication::applicationName(), QCoreApplication::applicationName());
//    settings.setParent(this);
//    settings.setPath(settings.format(),settings.scope(),settings.applicationName());
//    settings.setSystemIniPath(QCoreApplication::applicationDirPath());
    settings.beginGroup(group);

    settings.setValue(key, value);
    settings.endGroup();
}

QVariant MainWindow::loadSettings(const QString &key, const QString &group, const QVariant &defaultValue)
{
  QSettings settings(QSettings::IniFormat, QSettings::SystemScope,
             QCoreApplication::applicationName(), QCoreApplication::applicationName());

    settings.beginGroup(group);
    QString filename = settings.value(key, defaultValue).toString();
    settings.endGroup();

    qInfo() << "loadSettings(): " << filename;

    if( filename != "" )
      simulation_open_file( QDir::currentPath() +"\\"+ filename );   // open EMG data file

    return filename;
}

// -----------------------------------------------------------------------------

qint64 MainWindow::simulation_read_data_from_file()
{
 for (int k = 0; k < TEMP_NCH; k++)
 {
  switch (simulation)
  {
      case SIMUL_REALTIME: return 0;
      case SIMULATION_CSV:
      {
        for (int i = 0; i < DSIZE2; i++)                        //  1024
          {
                if(stream.status() != QTextStream::Ok)    // CSV
                {
                    qCritical() << "Error read file, buff size: " << buff << endl;
                    return false; // check status before using the data
                }
                if(stream.status() == QTextStream::ReadPastEnd)
                {
  //                  stream.reset();
                    simulation = SIMULATION_STOP;
                    stream.seek(0);
                    qCritical() << "Error ReadPastEnd: " << endl;
                    return false; // check status before using the data
                }
                QString a;
                a = stream.readLine(9); // one chanel
                qInfo() << "Size bef" << a;

                if (stream.atEnd())
                   simulation = SIMULATION_STOP;
                readdata.append(a);
  //              for (int k = 0; k < a.length(); k++)
  //                {
  //                  QString liczba = "";
  //                  int m = 0;
  //                  if (a.at(k) != ',') {
  //                      liczba.append(a[k]);
  //                  }


                //        QByteArray buff = serial.readLine( BSIZE );
                //         stream << "siz:" << buff.length() << endl;
                //        for (int i = 0; i < buff.size(); i++) {
                //            stream << (uint16_t) buff[i] << ",";
                //        }
                //        stream << endl;
//                readdata.append(a);
  //              buff = reinterpret_cast<char[]>(a.data());

  //      qInfo() << stream.pos();
          }
      }
          break;
    case SIMULATION_WAV: // TO DO
//      while (wav_in->atEnd()) {
//        wav_in->read((char*)timeData[k].data(), (qint64) timeData.size() );

        static int i;
        ui->statusBar->showMessage(QString::number(i++));

//        qWarning()<<"rozm:" << buff.size();
        if(wav_in->atEnd() || i  > 100) //TODO
        {
            simulation = SIMULATION_STOP;
            ui->statusBar->showMessage("ST0P");
            qWarning()<<"read wav file i:" <<i<< "size:" << buff.size();
            return false;
        }

        buff = wav_in->readAll();

        return  buff.size();
//      }


          break;
    default:
      return 0;
  }

  if (timeData[k].size() >= DSIZE ){ // symulator, nie wymaga płytki z EMG
      return true;
    } else {
      qWarning()<<"NIE wczytano danych\n";
      return false;
    }

   // TODO binary optimise full CPU load                                                                          // read binary data
    {
//          qInfo() << file.pos();
           if( wav_in->atEnd() )
           {
//            if( file.pos() != 0)  // jezeli nie na początku pliku
              wav_in->seek(0);     // zacznij jeszcze raz czytać plik (zapętl)
              ui->actionRun->setChecked(false);
           }

          //    QThread::msleep(milisec);
//          qint64 size = wav_in->read(buff, DSIZE2);
//           size = wa/v_in->read(reinterpret_cast<char*>(timeData[k].data()), static_cast<uint>(timeData[k].size())*sizeof(double));

//              if( size != DSIZE2){
//          //            return  false;
//            qCritical() << "Error read file, buff size: " << size << endl;
//            if(size == -1)      // jeśli plik pusty lub nie istnieje
//              {
//                simulation = SIMUL_REALTIME;
//                return false;
//              }
//          }

//          readdata.append(buff);

          qInfo() << "timeData size: " << timeData.size() << endl;

    }
 }
}

void MainWindow::on_actionOtw_rz_triggered(bool checked)
{
    system("C:\\ProgramData\\DataTransfer\\DataTransfer.ini");
}

void MainWindow::on_actionZapisz_domy_lne_triggered()
{
    saveSettings();
}

void MainWindow::on_actionKatalog_triggered()
{
    char dst[512];
    QString b =  QDir::currentPath();
//    dst = b.data()
//    strcpy_s(dst,100, (char*)b);
  qInfo() << dst;
    system( (const char*) b.data() ); // todo
}

void MainWindow::on_textEdit_cursorPositionChanged()
{

}

void MainWindow::draw_bars_Hz_gap(int window_length, int  rms)
{
//    int a = 20;
    int n = DSIZE2 / window_length; // Hz (okno)

    meanData.resize(n);

    for(int j=0; j<n; j++) // słupki wypełniena
    {
//            meanData[j] = std::accumulate( timeData[j].begin(), timeData[j].end(), 0.0)/timeData[j].size();
        meanData[j] = static_cast<double>(j/n);
    }
}

// signal

//void MainWindow::simulation_changed(Simulation_Type)
//{
//  ui->actionSave->setEnabled( !ui->actionSave->isEnabled() );
//}
Simulation_Type MainWindow::find_source_file(QString filename)
{
    if( QFileInfo(filename).isFile() ) {
        if( simulation_open_file(filename) == false) {
            simulation = SIMULATION_STOP;
        }
        qDebug() << "Find source: " << filename << simulation;
        return simulation;
    }
    // find by extension

    // glob directory
    // may request user
}



//void MainWindow::set_simulation(const Simulation_Type &newSimul)
//{
//    simulation = newSimul;
//    emit simulation_changed(newSimul);
//}
void MainWindow::set_simulation(const Simulation_Type &newSimul)
{
//    simulation = newSimul;
        qDebug() << "Simulation tick";
    emit simulation_changed();
}

//void Counter::setValue(int value)
//{
//    if (value != m_value) {
//        m_value = value;
//        emit valueChanged(value);
//    }
//}
