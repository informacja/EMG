#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionRun, &QAction::triggered, this, &MainWindow::sendCommand);
    // connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));

    connect(ui->radioCh_1, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_2, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_3, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_4, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_5, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_6, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_7, SIGNAL(toggled(bool)), this, SLOT(update()));
    connect(ui->radioCh_8, SIGNAL(toggled(bool)), this, SLOT(update()));

    timeData.resize(NCH);
    for(int i=0; i< timeData.size();i++){
        timeData[i].resize(VSIZE*FRCNT);
        timeData[i].fill(0);
    }
    timeDataView.resize(NCH);
    for(int i=0; i< timeData.size();i++){
        timeDataView[i].resize(VSIZE*FRCNT);
        timeDataView[i].fill(0);
    }
    cnt=0;

    fftData.resize(FFT_SIZE);
    fftWin.resize(FFT_SIZE);

    magnitudeData.resize(NCH);
    for(int i=0; i < magnitudeData.size(); i++) {
        magnitudeData[i].resize(FFT_SIZE);   // should be FFT_SIZE/2, but for display optimalisation
    }

    phaseData.resize(FFT_SIZE/2);

    waveSignal.resize(VSIZE*FRCNT*NCH);
    waveSignal.fill(0);

    ui->statusBar->showMessage("No device");
    // ui->statusBar->showMessage("USB device connected");
    QString portname;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if(info.serialNumber()=="NXP-77"){
            // if(info.description()=="MCU VIRTUAL COM DEMO"){

            portname=info.portName();
            serial.setPortName(portname);
            if (serial.open(QIODevice::ReadWrite)) {

                serial.setBaudRate( serial.Baud115200,  serial.AllDirections);
                ui->statusBar->showMessage(tr("Device: %1").arg(info.serialNumber()));
                serial.clear();
            }
            else
            {
                ui->statusBar->showMessage(tr("Can't open %1, error code %2") .arg(serial.portName()).arg(serial.error()));
                return;
            }
            break;
        }
    }


    chart.gridNumX=FRCNT/NCH;
    chart.gridNumY=10;
    chart.minValueX= 1;
    chart.maxValueX= 125*FRCNT;
    chart.minValueY=-1;
    chart.maxValueY= 1;
    chart.chartMode=LinearChart;
    chart.dataSize=VSIZE*FRCNT;

    //        chart.chartMode=LogChart;
    //        chart.gridNumX=27;
    //        chart.gridNumY=8;
    //        chart.minValueX= 1;
    //        chart.maxValueX= 1000;
    //        chart.minValueY=-40;
    //        chart.maxValueY= 0;
    //        chart.dataSize=(VSIZE*FRCNT)/2;

    // Rectangular Window
    fftWin.fill(1);


    // Hann Window
    //    for(int i=0; i<DSIZE2;i++)
    //        fftWin[i]=(0.5*(1-cos(2*M_PI*i/(DSIZE2-1))));

    setAcceptDrops(true);
    on_textEditFeatures_textChanged();

    qDebug() << "\nLegenda gestów dłoni:";
    qDebug() << "00. Pomiar szumu referencyjnego";
    qDebug() << "01. Moutza moc";
    qDebug() << "02. Zaciśnięta pięść";
    qDebug() << "05. Kciuk w górę";
    qDebug() << "11. Victoria";    
    qDebug() << "13. Złączone 3 środkowe palce ";
    qDebug() << "18. serdecznySpiderMan w środek dłoni";    
    qDebug() << "19. małyPalec";

#ifndef Q_OS_MAC
    ui->pushButtonMac->setVisible(false);
#endif
    ui->checkBoxARMA->setChecked(true);
    ui->checkBoxARMA->setChecked(false); // hide vidgets
    ui->radioButtonSigVCom->setVisible(false);
    ui->radioButtonSigSimulateSer->setVisible(false);

    ui->labelSMOK->setVisible(false);
    ui->labelState->setVisible(false);
    ui->labelFeed->setVisible(false);
//    ui->spinBox_gestureNr->setValue(0);
//    ui->spinBox_personNr->setValue( 42);
//    ui->textEditFeatures->toPlainText()
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}

void MainWindow::sendCommand()
{
    if(ui->actionRun->isChecked()) {
         cnt=0;
        serial.clear();
        senddata.clear();
        senddata.resize(1);
        senddata[0]=static_cast<char>(128*ui->actionRun->isChecked());
        serial.write(senddata);
    }
}

void MainWindow::readData()
{
    // qDebug()<< serial.size();
    if (serial.size() >= DSIZE){

        qDebug()<< serial.size();
        readdata=serial.read(DSIZE);

        uint16_t *sample=reinterpret_cast<uint16_t*>(readdata.data());
        for(int i=0; i<VSIZE;i++){
            for(int j=0; j<NCH; j++)
                timeData[j][i+(cnt*VSIZE)]=(double)((*sample++)-32768)/32768.0;
        }
        double bias[NCH];
        for(int j=0; j<NCH; j++){

            bias[j]=0;

            for(int i=0; i<VSIZE;i++)
                bias[j]+=timeData[j][i+(cnt*VSIZE)];

            bias[j]/=VSIZE;

            for(int i=0; i<VSIZE;i++)
            {
                timeData[j][i+(cnt*VSIZE)]-=bias[j];
                if(ui->checkBoxVirtualSpace->isChecked())
                {
                    timeDataView[j][i+(cnt*VSIZE)] = timeData[j][i+(cnt*VSIZE)]+(j+0.5)/NCH*2-1;
                }
                else    timeDataView[j][i+(cnt*VSIZE)] = timeData[j][i+(cnt*VSIZE)];

            }
        }

        cnt++;
        if(cnt>=FRCNT) {
            cnt=0;
            if(!ui->actionRun->isChecked()){
                serial.clear();
                senddata.clear();
                senddata.resize(1);
                senddata[0]=0;
                serial.write(senddata);
            }
        }

        if(ui->checkBoxSpectrum->isChecked())
              calculateFFT(cnt);

        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    chart.drawLinearGrid(painter, centralWidget()->geometry());

    painter.setRenderHint(QPainter::Antialiasing, true);

//    painter.setCompositionMode(QPainter::CompositionMode_HardLight);


//          if(ui->radioCh_1->isChecked())
//              chart.drawLinearData(painter, timeData[0], chart.plotColors[0]);
//          if(ui->radioCh_2->isChecked())
//              chart.drawLinearData(painter, timeData[1], chart.plotColors[1]);
//          if(ui->radioCh_3->isChecked())
//              chart.drawLinearData(painter, timeData[2], chart.plotColors[2]);
//          if(ui->radioCh_4->isChecked())
//              chart.drawLinearData(painter, timeData[3], chart.plotColors[3]);
//          if(ui->radioCh_5->isChecked())
//              chart.drawLinearData(painter, timeData[4], chart.plotColors[4]);
//          if(ui->radioCh_6->isChecked())
//              chart.drawLinearData(painter, timeData[5], chart.plotColors[5]);
//          if(ui->radioCh_7->isChecked())
//              chart.drawLinearData(painter, timeData[6], chart.plotColors[6]);
//          if(ui->radioCh_8->isChecked())
//              chart.drawLinearData(painter, timeData[7], chart.plotColors[7]);

    if(ui->radioCh_1->isChecked())
        chart.drawLinearData(painter, timeDataView[0], chart.plotColors[0]);
    if(ui->radioCh_2->isChecked())
        chart.drawLinearData(painter, timeDataView[1], chart.plotColors[1]);
    if(ui->radioCh_3->isChecked())
        chart.drawLinearData(painter, timeDataView[2], chart.plotColors[2]);
    if(ui->radioCh_4->isChecked())
        chart.drawLinearData(painter, timeDataView[3], chart.plotColors[3]);
    if(ui->radioCh_5->isChecked())
        chart.drawLinearData(painter, timeDataView[4], chart.plotColors[4]);
    if(ui->radioCh_6->isChecked())
        chart.drawLinearData(painter, timeDataView[5], chart.plotColors[5]);
    if(ui->radioCh_7->isChecked())
        chart.drawLinearData(painter, timeDataView[6], chart.plotColors[6]);
    if(ui->radioCh_8->isChecked())
        chart.drawLinearData(painter, timeDataView[7], chart.plotColors[7]);


//    for( int i = 0; i < NCH; i++)
//    {
//         chart.drawLinearData(painter,  magnitudeData[i], chart.plotColors[i]);
//    }
//            chart.drawLogData(painter, magnitudeData);
}

void MainWindow::calculateFFT(int cnt)
{
//    FFT_WINDOW

    for(int k=0; k < NCH; k++) {
        for(int i=0;i<FFT_SIZE; i++){
            fftData[static_cast<uint>(i)].real(timeData[k][i]*fftWin[i]);
            fftData[static_cast<uint>(i)].imag(0);
        }

#if ARMADILLO_FFT
        fftData=arma::fft(fftData);
#else
        Fft::transform(fftData);
#endif
        for(int i=0;i<FFT_SIZE/2; i++) {
            magnitudeData[k][i] = abs(fftData[static_cast<uint>(i)])*1;
            //        phaseData[i]=arg(fftData[static_cast<uint>(i)]);
        }

        double max = *std::max_element(magnitudeData[k].begin(), magnitudeData[k].end());

        for(int i = 0; i<FFT_SIZE/2; i++) {
            if(max>0)
                magnitudeData[k][i]/=max;  //normalise
            magnitudeData[k][i]+=0.01-1; // saturate -40 dB
        }

        for(int i = 0; i<FFT_SIZE/2; i++) { // fill all window

//            timeData[k][FFT_SIZE - i] = magnitudeData[k][i];
//            timeData[k][FFT_SIZE - i*2+1] = magnitudeData[k][i];
        }
    }
    //    qDebug() << sizeof (timeData[0]);
}

void MainWindow::filterData()
{
    //    double mac=0;
    //    for(int i=0;i<VSIZE*FRCNT;i++){

    //        for(int n=0;n<5;n++)
    //        mac+=timeData[0][i+n]
    //    }
    //timeData[1][i]=timeData[0][i]
}

void MainWindow::on_actionOpen_triggered()
{
//    QString FileName = ui->spinBox_gestureNr->text() + ui->spinBox_personNr->text() + ".wav";
//    FileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home", tr("Data (*.dat)"));
//    QFile file(FileName);
//    if (!file.open(QIODevice::ReadOnly))
//        return;
    //file.read(reinterpret_cast<char*>(timeData[0].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));

//    for(int j=0; j<NCH; j++)
//        file.read(reinterpret_cast<char*>(timeData[j].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));
//    file.close();

        QString FileName;
        FileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home", tr("Data (*.wav)"));

        loadFile((FileName));
//        calculateFFT(0);
}

void MainWindow::on_actionSave_triggered()
{
    QString FileName = "/home";
    FileName =  QString("%1").arg( ui->spinBox_gestureNr->value(), 2 , 10, QChar('0')) +
                QString("%1").arg( ui->spinBox_personNr->value(), 3 , 10, QChar('0')) + ".wav";
    //FileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home", tr("Data (*.dat)"));
    FileName = QFileDialog::getSaveFileName(this, tr("Save File"), FileName, tr("Data (*.wav)"));
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    //---
    int k=0;
    for(int i=0; i<VSIZE*FRCNT;i++){
        for(int j=0; j<NCH; j++)
            waveSignal[k++]=static_cast<short>(timeData[j][i]*32767);
    }

    WaveHeaderEx waveHdr;
    CreateWaveHeader(waveHdr, NCH, 2048,  static_cast<uint>(waveSignal.size()/NCH));

    qDebug()<<"Channels"<<waveHdr.Channels;
    qDebug()<<"SampFreq"<<waveHdr.SampFreq;
    qDebug()<<"dwSampleLength"<<waveHdr.dwSampleLength;
    qDebug()<<"DataLength"<<waveHdr.DataLength;

    qDebug()<<waveSignal.size();

    file.write(reinterpret_cast<char*>(&waveHdr), static_cast<uint>(sizeof(waveHdr)));
    file.write(reinterpret_cast<char*>(waveSignal.data()), static_cast<uint>(waveSignal.size()*sizeof(short)));

    //---
    //    for(int j=0; j<NCH; j++)
    //        file.write(reinterpret_cast<char*>(timeData[j].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));

    file.close();

    QFileInfo fileInfo(file.fileName());
    ui->groupBox_2->setTitle( fileInfo.fileName());
}

void MainWindow::on_pushButton_clicked()
{
    on_actionSave_triggered(); // save file
    static int i;
    if( ui->spinBox_gestureNr->value() < *std::max_element(gestureNr.begin(), gestureNr.end()))
    {
        i++;
        ui->spinBox_gestureNr->setValue( gestureNr.at(i % gestureNr.count()) );
    }
    else
    {
         ui->spinBox_gestureNr->setValue( 0 );
         ui->spinBox_personNr->setValue( ui->spinBox_personNr->value()+1 );
    }
}

void MainWindow::on_textEditFeatures_textChanged()
{
    QString data = ui->textEditFeatures->toPlainText();    
    QStringList strListGestureNr = data.split(QRegularExpression(" "), Qt::SkipEmptyParts);
    gestureNr.clear();
    for(auto i : strListGestureNr)
    {
        gestureNr.append(i.toUInt());
    }
    if(gestureNr.size())
        ui->spinBox_gestureNr->setValue(gestureNr.first());
}

//#include <QMimeData>
//#include <QDragEnterEvent>
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        ui->statusBar->setStatusTip(fileName);
        loadFile(fileName);
//        ui->listWidget->addItem(fileName);
    }

}

void MainWindow::loadFile( QString FileName )
{
    QFile file(FileName);
    {
        if (!file.open(QIODevice::ReadOnly))
            return;

        // qDebug()<< file.size();

        WaveHeaderEx waveHdr2;

        waveSignal.resize((file.size()-sizeof(waveHdr2))/sizeof(short));
        waveSignal.fill(0);
        file.read(reinterpret_cast<char*>(&waveHdr2), static_cast<uint>(sizeof(waveHdr2)));
        file.read(reinterpret_cast<char*>(waveSignal.data()), static_cast<uint>(waveSignal.size()*sizeof(short)));
        file.close();

        //        for(int j=0; j<NCH; j++)
        //            file.read(reinterpret_cast<char*>(timeData[j].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));

        int k=0;
        for(int i=0; i<(int)waveHdr2.dwSampleLength/waveHdr2.Channels; i++) {
            for(int j=0; j< waveHdr2.Channels; j++){
                timeData[j][i] = static_cast<double>(waveSignal[k++]/32767.0) ;
//                timeDataView[j][i] = timeData[j][i] + (j+0.5)/waveHdr2.Channels*2-1;;
            }
        }
        virtualSeparate();

        qDebug()<<"Channels"<<waveHdr2.Channels;
        qDebug()<<"dwSampleLength"<<waveHdr2.dwSampleLength;
        qDebug()<<"DataLength"<<waveHdr2.DataLength;
        qDebug()<<waveSignal.size();

        //    CreateWaveHeader(waveHdr1, NCH, 96000,  static_cast<uint>(waveSignal.size()*sizeof(short)/NCH));

        update();
    }
}


void MainWindow::virtualSeparate()
{
    if(ui->checkBoxVirtualSpace->isChecked())
    {
        for (int k = 0; k < NCH; k++) {
            for (int i = 0; i < VSIZE*FRCNT; i++) {
                timeDataView[k][i] = timeData[k][i] + (k+0.5)/NCH*2-1; // separation normalized
            }
        }
    }
    else
    {
        for (int k = 0; k < NCH; k++) {
            for (int i = 0; i < VSIZE*FRCNT; i++) {
                timeDataView[k][i] = timeData[k][i];
            }
        }
    }
}

void MainWindow::on_actionMaximize_triggered()
{
    if(!ui->actionMaximize->isChecked())
        this->showNormal();
    else
        this->showFullScreen();
}

void MainWindow::on_pushButtonMac_clicked()
{
    this->on_pushButton_clicked();
}

void MainWindow::on_checkBoxARMA_stateChanged(int arg1)
{    
    ui->dockWidgetHorizontal->setVisible(arg1);
    ui->dockWidgetVertical->setVisible(arg1);
}


void MainWindow::on_groupBox_clicked()
{

    ui->radioCh_1->setChecked( !ui->radioCh_1->isChecked() );
}

void MainWindow::on_checkBoxVirtualSpace_stateChanged(int arg1)
{
    virtualSeparate();
    update();
}
