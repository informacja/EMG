#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QTimer>
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

   qDebug() << "setupUi:" << myTimer.elapsed() << "ms"; myTimer.start();

    connect(&thread, SIGNAL(tick()), this, SLOT(externalThread_tick()));
    connect(ui->actionRun,  SIGNAL(triggered()), this, SLOT(sendCommand()));
    connect(ui->actionSignal, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->actionSpectrum, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->actionRms,  SIGNAL(triggered()), this, SLOT(update()));
//    connect(this, SIGNAL(simulation_changed()), this, SLOT( set_simulation(Simulation_Type) ));
//    connect(ui->spinBox_hz, SIGNAL(valueChanged()), this, SLOT( ui->pwmValue1->setValue(ui->spinBox_hz->value()) ));
    connect(ui->spinBox_HiPass, SIGNAL(valueChanged(int)), this, SLOT( set_butterworth_HiPass(int) ));
    connect(ui->spinBox_BandStop, SIGNAL(valueChanged(int)), this, SLOT( set_butterworth_BandStop_fq(int) ));
    connect(ui->spinBox_BandStop_width, SIGNAL(valueChanged(int)), this, SLOT( set_butterworth_BandStop_width(int) ));
    connect(ui->lineEdit_path, SIGNAL(textChanged(QString)), this, SLOT( set_lineEdit_qnique_filename(QString) ));

//    QTimer *timer = new QTimer(this);
//        connect(timer, SIGNAL(timeout()), this, SLOT(this->paintEvent()));
//        connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
//        timer->start(50);
//    m_timer.start(1000, this);

//    connect(this->simulation, SIGNAL(simulation_changed(Simulation_Type)), this->simulation, SLOT(simulationSet(const Simulation_Type& )));
//    connect(slider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged(int)));

    ui->statusBar->showMessage("No device");
    set_simulation( GENERATE_SIGNAL );
//    set_simulation( SIMULATION_STOP );

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
    chart.maxValueX= WSIZE;
    chart.minValueY= 0;
    chart.maxValueY= 1;
    chart.chartMode=LinearChart;
    chart.dataSize=WSIZE;
    chart.backgroundColor = QColor::Invalid;

    alloc_memory_sub_constructor();
    pointers_set_null();
    alloc_files();

    isinverse = 0;          // for fft
    coutingDownToZero = 0;

    for (int i = 0; i < DSIZE2; i++)
    {
       hamming[i] = static_cast<float>( (0.54-((0.46) * cos(2*M_PI*i/(DSIZE2-1)))) );
       hann[i]    = static_cast<float>( 0.5 * (1 - cos(2*M_PI*i/DSIZE2)) );
    }

//    const int order = 4; // 4th order (=2 biquads)
//    Iir::Butterworth::LowPass<order> f;
//    const double samplingrate = DSIZE; // Hz
    const double samplingrate = DSIZE2; // Hz
    const double cutoff_frequency = 50; // Hz
    fHiPass.setup(samplingrate, cutoff_frequency);
    fBandStop.setup(samplingrate, cutoff_frequency, 10);

    setAcceptDrops(true);
    ui->spinBox_HiPass->setMaximum(WSIZE);
    ui->spinBox_BandStop->setMaximum(WSIZE);
    ui->spinBox_BandStop->setValue(static_cast<int>(cutoff_frequency));

    // Output WAVE settings
    format.setCodec("audio/pcm");
    format.setSampleRate(DSIZE2);                         // Hz sample per second
    format.setChannelCount(1);                              // NCH TODO:
    format.setSampleSize(sizeof(in[0][0])*8);           // sizeof(double) => 8 ( I multiplayng by 4 to get valid 32 bits)
    qDebug() << "SampleSize" << sizeof( in[0][0])*8 ;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SampleType::Float); // nie ma double co zrobić?

//    file_out.setFileName( get_unique_filename(FILE_NAME EXT) ); // depracated to uninitlalize
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

    if( !QCoreApplication::arguments().contains("-nosettings", Qt::CaseSensitivity::CaseInsensitive) )
        if( !serial.isOpen() )
            input_file = loadSettings().toString();     // ścieżka do pliku z zapisu EMG

    qDebug() << "Symulacja?" << simulation;

    if( simulation == SIMULATION_STOP )
        simulation = find_source_file(input_file);

    switch(simulation) // teoretycznie do usunięcia
    {
        case SIMUL_REALTIME:     // nawiązano połączenie z płytką
        {
//            file_out.open(QIODevice::WriteOnly | QIODevice::Append);    // bin
            QString fName = get_unique_filename(FILE_NAME ".wav", true);
            qDebug() << "Plik do zapisu" << wav_out->open( fName, format) << fName;
        } break;
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
            set_simulation(GENERATE_SIGNAL);
            // szukaj plików do otwarcia
        break;
//    default: break;
    }

    file_csv.open(QIODevice::Append);
    stream.setDevice( (QIODevice*) &file_csv );

//  ui->textEdit->setVisible(ui->actionSave->isChecked());
    ui->lineEdit_fileN->setText( wav_out->fileName() );
    ui->lineEdit_path->setText( SAMPLE_DIR );

#ifndef ALLOW_USE_FILTERS
    ui->groupBox_window->setDisabled(1);
    ui->groupBox_bw_filtr->setDisabled(1);
#endif

#ifdef DISABLE_FILTERS_ON_STARTUP
    ui->radioBtn_rect->setChecked(true);
    ui->checkBox_bandStop->setChecked(false);
    ui->checkBox_highPass->setChecked(false);
    ui->actionSignal->setEnabled(true);
#endif

//#ifdef QT_DEBUG
//    ui->selectInput2->setChecked(false);
//    ui->selectInput3->setChecked(false);
//#endif //QT_DEBUG

        
            ui->selectInput1->setStyleSheet("border: 1px solid red;\
                                     border-radius: 3px;\
                                     padding: 2px 2px 2px 2px; \
                                    ");
    ui->selectInput2->setStyleSheet("border: 1px solid green;\
                                     border-radius: 3px;\
                                     padding: 2px 2px 2px 2px; \
                                    ");
    ui->selectInput3->setStyleSheet("border: 1px solid darkCyan;\
                                     border-radius: 3px;\
                                     padding: 2px 2px 2px 2px; \
                                    ");


    ui->radioBtn_hamm->hide();
//    ui->tab_config->setMaximumWidth(10);

//    QWidget *wid=new QWidget();
//    QVBoxLayout *layout=new QVBoxLayout();
//    for (int i = 0; i < 10; ++i){
//    QPushButton *button = new QPushButton();
//    button->setText(QString::number(i));
//    QObject::connect(button, SIGNAL(clicked(bool)), wid, SLOT(onClicked(bool)));
//    layout->addWidget(button);
//    wid->setLayout(layout); // Add the button to the layout
//    wid->show();
//}



//    QSplitter *splitter = new QSplitter(this);

//    QFileSystemModel *model = new QFileSystemModel;
//       model->setRootPath(QDir::currentPath());
//       QTreeView *tree = new QTreeView(splitter);
//       tree->setModel(model);
////         QListViewPrivate *listview = new QListViewPrivate;
//         QTreeView *treeview = new QTreeView;
//         QTextEdit *textedit = new QTextEdit;

//         splitter->resize(300,200);
//         splitter->move( 0 , 150);
//         tree->setVisible(true);
//         splitter->setChildrenCollapsible(true);


//         splitter->
//         tree->resize(100,100);//setWindowwidth(100);

////         splitter->addWidget(listview);
//         splitter->addWidget(treeview);
//         splitter->addWidget(textedit);
////       QList a(3,2);
//         QLabel *label = new QLabel(this->ui->dockWidget);

////         label-move()
//         label->setFrameStyle( QFrame::Sunken);
//         label->setText("Nie wykryto płytki\nPodłącz płytkę z elektrodami");
//         label->setAlignment(Qt::AlignVCenter );
//         label->setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable);
//         label->setWindowModality(Qt::WindowModality::WindowModal);
//         label->setMargin(0);


         // (layout setup not shown)
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

    for (int i = 0; i < 3; i++) {
        fi[i] = i*60*M_PI/180;
    }

}

void MainWindow::pointers_set_null()
{
    wav_out = nullptr;
    wav_in  = nullptr;
    wait_for_data = false;
}
void MainWindow::alloc_files()
{
  wav_in = new WavFilerReader(nullptr);
  wav_out = new WaveFileWriter(nullptr);
}

MainWindow::~MainWindow()
{    
    wav_in->close();
//    qDebug() << "len"<< wav_out->get_len();
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

//Proces powstawania odprogramowania
//1.grafica desin
//2. okodowanie designu
//3 rediina
// 4 integracja z sprz etaem, przyciski. kontrolki,
//5zrobienie sprz etu



//sniadanie
//rozmowa z grafikami
//z szefem
//robienie swojego




// =============================================================================
/* ToDo:
 *
 * spektrum / 2 => 512 Hz
   Emulowanie wejścia np. odtwarzanie nagrania
   szumy, typu piła, wygasające
 * rysowanie widma 2 pola
 * RMS
 * Github kody publikacja - does't allowed by King
 * flitracja na 50Hz obecnie trzeba podać 100 dla 50
    zapis i odczyt
    lista plikow   
    jak regulować FPS => timer

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
    //     qDebug()<<"serial"<<serial.size();
         qDebug()<<"sy"<< simulation;
    // obsluga przycisku akcji (play/pause)
    if( simulation == SIMULATION_STOP || simulation == GENERATE_SIGNAL ) {
        ui->statusBar->showMessage("Przenieś i upuść na program plik typu (WAV, CSV) drag&drop SIMULATION_STOP",1000);
//        ui->actionRun->setChecked(false);
//        serial.clear();

    } else {
        auto_actionRun_serial_port(3);                                             // automatyczny start rysowania po ekranie
    }
    //  int size = (DSIZE * ui->spinBox_nDataPerFile->text().toInt());
    //  if(wait_for_data)
    //   if( serial.size() >= size)
    //   {
    //     timeData.resize(size);
    //      readdata = serial.readAll();
    //     uint16_t* sample = reinterpret_cast<uint16_t*>(readdata.data());
    //     for (int i = 0; i < size; i++)
    //     {
    //       timeData[0][i]=(*sample++)/65535.0;
    //     }
    //     // convert
    //    wav_out->write(reinterpret_cast<char*>(timeData[0].data()), static_cast<uint>(timeData[0].size())*sizeof(double));
    //    wait_for_data = false;
    //    ui->progressBar->setValue(100);

    //   }
    //   else {
    //      ui->progressBar->setValue(serial.size()/size);
    //   }


    //  QThread::msleep(1);

    if(ui->actionRun->isChecked())
        //    if( buff.size() > 0)                                                        // serial port lub z pliku
    {
        //    qDebug() << "simulation:  " <<simulation;
//        if(buff.size() == 0)
//        {
//            if(simulation)                                  // czytaj dane z pliku
//            {
                //            simulation_read_data_from_file();
//            }
//            else
            if( serial.size() >= DSIZE  )              // zapisz do pliku
            {
              readdata = serial.read(DSIZE);
//              qDebug() << readdata.size() << timeData.size();//                timeData[0] = readdata.;
//                readdata = serial.readAll();

                if( ui->actionSave->isChecked() || coutingDownToZero )
                    save_to_file( 0 );
//                return readdata.size();
            }
//                 qDebug() << serial.size();
            //        else
            //            return;
//        }

        signal_source();        // load from LPC 1347, load from wav or generate signal

        process_signals();      // fft, rms, korelacja

        update();//      present_data();

//        if(ui->actionRun->isChecked())
//        if (simulation == SIMUL_REALTIME)
            sendCommand();

            qDebug() << serial.size();
//        readdata.resize(0); // don't move, clear readdata only if was displayed

//        if (simulation == GENERATE_SIGNAL)
//            repaint();    // 100% cpu if emmit thread tick 1ms

        ///////////////////////// debug
        ///
#ifdef QT_DEBUG
        static int w;
        qDebug() << "externalThread_tick" << ++w;
#endif
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

    if(ui->actionSignal->isChecked())
    {
//        timeData.resize(WSIZE);
        if(ui->selectInput1->isChecked())
        {
              chart.plotColor=Qt::red;
              chart.drawLinearData(painter, timeData[0]);
        }
        if(ui->selectInput2->isChecked())
        {
            chart.plotColor=Qt::green;
            chart.drawLinearData(painter, timeData[1]);
        }

        if(ui->selectInput3->isChecked())
        {
            chart.plotColor=Qt::darkCyan;
            chart.drawLinearData(painter, timeData[2]);
        }
    }
    if( ui->actionSpectrum->isChecked())
    {
        chart.plotColor=Qt::gray;
        chart.drawLinearData(painter, spectrum[0]);
    }

    if(ui->actionRms->isChecked()) {
        chart.plotColor=Qt::cyan;
        chart.drawBarsData(painter, meanData);
    }

    ////////////////////////////////////////////////////////

//    QChartView *chartView = new QChartView;
//    QValueAxis *axisX = new QValueAxis;
//    axisX->setRange(10, 20.5);
//    axisX->setTickCount(10);
//    axisX->setLabelFormat("%.2f");
//    chartView->chart()->setAxisX(axisX, series);
//    QLineSeries  *series = new QLineSeries();
//    series->setPointLabelsVisible(true);    // is false by default
//    series->setPointLabelsColor(Qt::black);
//    series->setPointLabelsFormat("@yPoint");
//    chart.textColor = 0xFFFF00;
//    chart.
    QPen pen;
    pen.setWidth(1);
//    pen.setColor(backgroundColor);
    painter.setPen(pen);
//    painter.setBrush(backgroundColor);
//    painter.drawRect(geometry);
            QFont font;
            font.setPointSize(8);
            painter.setFont(font);
            pen.setColor(0x00aaaaaa);
            pen.setColor(Qt::white);
            painter.setPen(pen);

            int gx=geometry().x()+MX;
            int gy=geometry().y()+MY;
            int gw=geometry().width()-(2*MX);
            int gh=geometry().height()-(2*MY);

            int dx=gw/static_cast<double>(10);
            int dy=gh/static_cast<double>(10);

            for(int px=0; px<=300; px++)
                painter.drawText(QPointF(gx-(font.pointSize()/4)+px*dx, gy+gh+(font.pointSize()*2)),
                                 QString().sprintf("%d",static_cast<int>(0+(1*px)/10)));

            painter.drawText(QPointF(gw+50+(font.pointSize()), gh+30+(font.pointSize())),
                             QString().sprintf("%s","[Hz]"));

            for (int i = 0; i < 1;i++)
            {
//                painter.drawText(QPointF(33+i*(1*i)-(font.pointSize()), 1+i+(font.pointSize()*2)),
//                                 QString().sprintf("%s","Beta"));

//                painter.drawText(QPointF(gx+(12-11)*1, gy-font.pointSize()), QString().sprintf("%.1f","markerX"));
//                painter.drawText(QPointF(gx+gw+font.pointSize(), gy+(2-1)*1), QString().sprintf("%.1f","markerY"));
            }

        if (!serial.isOpen()) {
            painter.drawText(QPointF(gw/3+(font.pointSize()), 90-(font.pointSize())),
                             QString().sprintf("%s","Nie nawiązano połączenia, spróbuj podłączyć płytkę i uruchomić program ponownie"));

        }

    if ( coutingDownToZero )
    {
//        chart.plotColor = Qt::darkRed;
        int px = MX - 5;
        int shift = px/3*2;
        painter.drawRoundedRect(gw+shift*2-1, px+shift+1, px, px, px, px);
    }
    ////////////////////////////////////////////////////////

#ifdef FPS
    fps.paintEvent(event);
#endif

#ifdef QT_DEBUG
    static int w;
    qDebug() << "paintEvent" << ++w;
#endif
//printf("FPS is %f\n", m_frameCount / (float(m_timer.elapsed()) / 1000.0f));
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

void MainWindow::save_to_file( bool add_seconds)
{

  QVector<QVector<float>> wavData;

  if ( coutingDownToZero-- >= 0 )
  {
    if( coutingDownToZero+1 == ui->spinBox_nDataPerFile->value() ) { // csv date
      stream <<  ui->lineEdit_path->text()<< "/" << ui->lineEdit_fileN->text()
             << " " << QTime::currentTime().toString() << " " << QDate::currentDate().toString() << endl;
    }
    ui->progressBar->setValue( ui->spinBox_nDataPerFile->value() - coutingDownToZero);
//    qDebug() << "to zero count:" << coutingDownToZero;
  }

  double *pSrc = nullptr;
  float  *pDsc = nullptr;

  for (int k = 0; k < NCH; k++)
  {
     pSrc = timeData[k].data();
     pDsc = static_cast<float*>(wavData[k].data());
    for (int i = 0; i < timeData[0].size(); i++)
    {
        *pDsc++ = static_cast<float>(*pSrc++);
    }
//}

//      if(add_seconds)
      {
//          stream << "[" << QDateTime::currentMSecsSinceEpoch() << "]" << readdata << endl;
          // no csv
//          file_out.write(( QString::toUtf8( QDateTime::currentMSecsSinceEpoch() ) ));
      }

        wav_out->write(reinterpret_cast<char*>(wavData[k].data()), static_cast<uint>(wavData[k].size())*sizeof(wavData[0][0]));

        qInfo() <<"zapisano kanał "<<  k << "size(): " << wavData[k].size()*sizeof (wavData[0][0]) <<  QDateTime::currentMSecsSinceEpoch();
        for (int i = 0; i < wavData[k].size(); i++)
        {
            stream <<  wavData[k][i] << ",";    // out.csv
        }
        stream << endl;
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

void MainWindow::on_actionSave_triggered()
{
     ui->lineEdit_fileN->setVisible(ui->actionSave->isChecked());
//     if(ui->actionSave->isChecked() == true)
//     {
//         if(file_out.isOpen())
//            file_out.close();
//         file_out.setFileName(ui->tEdit_out->toPlainText());
//         file_out.open(QIODevice::Append);
//     }
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
            set_simulation(SIMULATION_STOP);
//            simulation = ;
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
    simulation = newSimul;
        qDebug() << "Simulation tick, new SimType: " << newSimul;
    emit simulation_changed(newSimul);
}

//void Counter::setValue(int value)
//{
//    if (value != m_value) {
//        m_value = value;
//        emit valueChanged(value);
//    }
//}



// -----------------------------------------------------------------------------

QString MainWindow::get_unique_filename(QString filename, bool allow_empty)
{
  int i = 0;
  if(filename.isEmpty())
    filename = FILE_NAME EXT;

  QFileInfo fi(filename);

  while( fi.exists() )
  {
    if(allow_empty)
      if( fi.size() == 0 )  // jeśli plik pusty, to nadpisz
        break;
    i++;
    QRegularExpression re("(\\d*)");
    filename = "";
    if ( !fi.path().isEmpty() && fi.path() != ".")
        filename = fi.path() + "/";
    filename += fi.completeBaseName().replace(re, "") + QVariant(i).toString() + "." + fi.completeSuffix();
    fi.setFile(filename);
  }
  return filename;
}
// ------------------------------------------------------------------------------
void showFileInFolder(const QString &path){
    #ifdef _WIN32    //Code for Windows
        QProcess::startDetached("explorer.exe", {"/select,", QDir::toNativeSeparators(path)});
    #elif defined(__APPLE__)    //Code for Mac
        QProcess::execute("/usr/bin/osascript", {"-e", "tell application \"Finder\" to reveal POSIX file \"" + path + "\""});
        QProcess::execute("/usr/bin/osascript", {"-e", "tell application \"Finder\" to activate"});
    #endif
}

void MainWindow::on_pushButto_kat_clicked(){

  if( ui->lineEdit_path->text().isEmpty() )
    QDesktopServices::openUrl( QUrl::fromLocalFile( QDir::currentPath() ));
  else {
    QString path = QDir::currentPath()+ "/" +ui->lineEdit_path->text() ;
    if( !QDesktopServices::openUrl( QUrl::fromLocalFile( path )) )
        ui->statusBar->showMessage("Nie mogę otworzyć sieżki " + path );
  }
}

void MainWindow::on_pushButton_openFile_clicked()
{
  wav_out->close();
  QString path = QDir::currentPath()+ "/" +ui->lineEdit_path->text()+ "/" +ui->lineEdit_fileN->text() ;
  showFileInFolder(path);
}

void MainWindow::set_butterworth_BandStop_fq(int cutoff_frequency){
  fBandStop.setup( DSIZE, cutoff_frequency, ui->spinBox_BandStop_width->value()*2);
}

void MainWindow::set_butterworth_BandStop_width(int width){
  fBandStop.setup( DSIZE, ui->spinBox_BandStop->value(), width);
}
void MainWindow::set_butterworth_HiPass(int cutoff_frequency){
  fHiPass.setup( DSIZE, cutoff_frequency);
}

void MainWindow::on_radio_saveAllDir_clicked(){
  ui->lineEdit_path->setText( SAMPLE_DIR "/mix");
}
void MainWindow::on_radio_handOpen_clicked(){
    ui->lineEdit_path->setText( SAMPLE_DIR "/hand/open");
}
void MainWindow::on_radio_handClose_clicked(){
    ui->lineEdit_path->setText( SAMPLE_DIR "/hand/closed");
}
void MainWindow::on_radioButton_clicked(){
  ui->lineEdit_path->setText( SAMPLE_DIR "/first_finger");
}
void MainWindow::on_radioButton_2_clicked(){
  ui->lineEdit_path->setText( SAMPLE_DIR "/thumb");
}

inline void MainWindow::load_data_from_serialport()
{
  uint16_t* sample = reinterpret_cast<uint16_t*>(readdata.data());
//  if (simulation == SIMULATION_WAV) // not needet, it cheked above
//  {
//      static size_t krok;
//      sample = reinterpret_cast<uint16_t*>(buff.data());
//      krok += DSIZE;
//      sample += krok;
//        qDebug() <<"krok:" <<  krok<< krok+NCH*DSIZE2;
//      ui->statusBar->showMessage(QString::number(krok));

//      if( krok >= buff.size()-DSIZE)
//      {
//          qDebug() <<"exit at krok:" <<  krok;
//        ui->actionRun->setChecked(false);
//        buff.clear();
//        buff.resize(0);
//        krok = 0;
//        simulation=SIMULATION_STOP;
//        return;
//      }
//  }

  for(int i=0; i<DSIZE2; i++) // czy tu nie powninno byćH D2SIZE
  {
    for(int k=0; k<NCH; k++)
    {
      timeData[k][i]=(*sample++)/65535.0;

//      float freq =200; test[i].r = sin(2 * M_PI * freq * i / DSIZE2), test[i].i = 0;  test[i].i = 0; test[i].r = kiss_fft_scalar (*sample)/65535.0;
#ifdef ALLOW_USE_FILTERS
   // filtracja
      if(ui->radioBtn_rect->isChecked()) {
        // do nothing, just assingn
      }
      else if (ui->radioBtn_hann->isChecked()) {
        timeData[k][i] *= static_cast<double>(hann[i]);       //(*sample)/65535.0;
      }
      else if (ui->radioBtn_hamm->isChecked()) {
        timeData[k][i] *= static_cast<float>(hamming[i]);       //(*sample)/65535.0;
      }

      if( ui->checkBox_bandStop->isChecked() ) {
        timeData[k][i] = fBandStop.filter( timeData[k][i] );
      }

      if( ui->checkBox_highPass->isChecked() ) {
        timeData[k][i] = fHiPass.filter( timeData[k][i] );
      }
#endif // APPLY_FILTERS

      (in[k]+i)->r = static_cast<float>(timeData[k][i]);
      (in[k]+i)->i = 0;
    }
  }
}

void MainWindow::on_toolButton_return_clicked()
{
    ui->toolButton_enter->animateClick();
}

void MainWindow::on_toolButton_enter_clicked()
{
  QString fName = "";

  ui->progressBar->setRange(0, ui->spinBox_nDataPerFile->value());
  ui->progressBar->setValue(0);

    wav_out->close();
    if ( ui->lineEdit_path->text().isEmpty() )
        fName = ui->lineEdit_fileN->text();
    else
    {
      QDir dir;// We create the directory if needed
      if (!dir.exists(ui->lineEdit_path->text()))
          dir.mkpath(ui->lineEdit_path->text()); // You can check the success if needed

        fName = ui->lineEdit_path->text()+ "/" +ui->lineEdit_fileN->text();
    }
    QFileInfo fi( get_unique_filename(fName) );
    ui->lineEdit_fileN->setText( fi.completeBaseName()+ "." +fi.completeSuffix() );

    fName = ui->lineEdit_path->text()+ "/" +ui->lineEdit_fileN->text();
    wav_out->open( fName, format );
    coutingDownToZero =  ui->spinBox_nDataPerFile->value();
    qDebug() << "is open wav" << wav_out->isOpen() << wav_out->fileName();
    ui->progressBar->setValue(100);
}
// ----------------------------------------------------------------------------------------
void MainWindow::set_lineEdit_qnique_filename(QString path)
{
  QString uniqName = get_unique_filename(path+ "/" + ui->lineEdit_fileN->text() );
  QFileInfo fi(uniqName);
  ui->lineEdit_fileN->setText( fi.fileName() );
}

// ----------------------------------------------------------------------------------------

void MainWindow::on_pushButton_clicked()
{
    wait_for_data = true;
    serial.readAll();
}

// ----------------------------------------------------------------------------------------

inline void MainWindow::process_signals()
{
    spectrum[0].fill(0);        // uzywany jako wynik wymnozenia widm 3-ch kanlow

    for (int k = 0; k < NCH; k++)
    {
        kiss_fft( cfg, in[k], out[k] );

        for (int i = 1; i < WSIZE; i++) // fft gives redundant spectrum, use only half of window  (WSIZE)
        {
            if ( i >= DSIZE2 ) // na wypadek zwiękaszania pętli np. razy 2
            {
                //          break;
            }
            double normBinMag = sqrt(SQUARE((out[k]+i)->r) + SQUARE((out[k]+i)->i))/51.2 ; // do konca nie wiem czemu tu musze mnozyc przec 8
            //                   normBinMag = sqrt(SQUARE(test[i].r) + SQUARE(test[i].i))  ; // do konca nie wiem czemu tu musze mnozyc przec 8
            double mag = normBinMag;

            int scalar = 1;
            i *= scalar;       // przedział zmiennej i: od 0 do 512 mnożony razy dwa


            if (k == 0 )
            {
                spectrum[0][i] = mag ;            // TODO nie mieści się na wykresie//                  spectrum[k][i] = (out[0]+i)->r * hamming[i];
            }
//            else if (k == 1){
//                spectrum[0][i] *= mag * ui->pwmValue2->value(); // razy wspoczynnik z sowaka
//            }else {
//                spectrum[0][i] *= mag * ui->pwmValue3->value(); // razy wspoczynnik z sowaka
//            }
            //                  spectrum[k][i-1] = mag;            // TODO nie mieści się na wykresie//                  spectrum[k][i] = (out[0]+i)->r * hamming[i];


            int a = 10;
//            if( a < i && i < DSIZE-a) // Hz
//            {
//                timeData[1][i] = rms(&spectrum[0][i-a],a*2);
//                timeData[1][i-1] = timeData[1][i];
//            }
//            else
//            {
//                timeData[1][i] = 0;
//                timeData[1][i-1] = 0;
//            }

            //                   a = 20;
//            int n = DSIZE2 / a; // Hz (okno)

//            if( meanData.size() != n )
//                meanData.resize(n);

//            for(int j=0; j<n; j++) // słupki wypełniena
//                //                  if ( n > 0 && i % n == 0 )
//            {
//                //            meanData[j] = std::accumulate( timeData[j].begin(), timeData[j].end(), 0.0)/timeData[j].size();
//                //                      meanData[i/n] = i/n;
//                meanData[j] = (double) j/n;
//            }

//            i /= scalar;
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

    int d = WSIZE/NBARS;

    if( meanData.size() != NBARS )
        meanData.resize(NBARS);

    //        ui->statusBar->showMessage( "Rozmiar d: " + QString::number(DSIZE2));

    for (int i = 0; i < NBARS; i++) {
        //            meanData[i]=(double)i/d;
        //             if( a < i && i < DSIZE2-a) // Hz
        meanData[i] = rms(&spectrum[0][(d)*i],d);
        //            meanData[i]=rms(&spectrum[0][d*q],0);
    }
}

// ----------------------------------------------------------------------------------------

void MainWindow::generate_3_signals(int speed, int gap, bool mirror )
{
    static int ink;
    double freq;

    ink += speed;
    int k = 0;
//    for (int k = 0; k < NCH; k++)
    {
        freq = ( ink + k * gap ) % 512 * ((mirror == false) ? 1 : 2);// 2*512 (efekt odbijania się od krawędzi)
        for (int i = 0; i < WSIZE; i++)
        {
            if( ui->selectInput1->isChecked() )
            {
                freq = ( ink + k * gap ) % 512 * ((mirror == false) ? 1 : 2);
                timeData[k][i] =((k+2.)/20)*sin(((2 * M_PI) * freq * i + fi[k]) / DSIZE2 );
            }
            else timeData[k][i] = 0;  k++;

            if( ui->selectInput2->isChecked()  )
            {
                freq = ( ink + k * gap ) % 512 * ((mirror == false) ? 1 : 2);
                timeData[k][i] = ((k+2.)/20)*sin(((2 * M_PI) * freq * i + fi[k]) / DSIZE2 );
            }
            else timeData[k][i] = 0; k++;

            if( ui->selectInput3->isChecked() )
            {
                freq = ( ink + k * gap ) % 512 * ((mirror == false) ? 1 : 2);
                timeData[k][i] = ((k+2.)/20)*sin(((2 * M_PI) * freq * i + fi[k]) / DSIZE2 );
            }
            else timeData[k][i] = 0; k = 0;

            in[k][i].i = 0;
//            in[0][i].r += timeData[k][i];

            in[0][i].r = timeData[0][i] + timeData[1][i] + timeData[2][i];                  // add signals for fft
        }
    }
}

// ----------------------------------------------------------------------------------------
void MainWindow::apply_filters()
{
    for (int k = 0; k < NCH; k++) {
        for (int i = 0; i < DSIZE2; ++i) {

            if(ui->radioBtn_rect->isChecked()) {
              // do nothing, just assingn
            }
            else if (ui->radioBtn_hann->isChecked()) {
              in[k][i].r *= (hann[i]);       //(*sample)/65535.0;
            }
            else if (ui->radioBtn_hamm->isChecked()) {
              in[k][i].r *= (hamming[i]);       //(*sample)/65535.0;
            }

            if( ui->checkBox_bandStop->isChecked() ) {
              in[k][i].r = fBandStop.filter( in[k][i].r );
            }

            if( ui->checkBox_highPass->isChecked() ) {
              in[k][i].r = fHiPass.filter( in[k][i].r );
            }
        }
    }
}

void MainWindow::signal_source()
{

    switch (simulation)
    {
        case GENERATE_SIGNAL:
            generate_3_signals(1, 10, true);
            apply_filters();
        break;
        case SIMUL_REALTIME:
        {
            load_data_from_serialport();
            //      get_data;
            break;
        }

        case SIMULATION_WAV: // read file
        {
            //      break;  // jeszcze nie zaimplementowano
        }
        case SIMULATION_STOP:
        default:
            qDebug() << "State: Simulation stop in externalThread_tick()";
            return;
    }
}
// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------
