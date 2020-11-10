#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
    cnt=0;

    fftData.resize(FFT_SIZE);
    fftWin.resize(FFT_SIZE);

    magnitudeData.resize(FFT_SIZE/2);
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


    chart.gridNumX=FRCNT/20;
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
                timeData[j][i+(cnt*VSIZE)]=((*sample++)-32768)/32768.0;


        }
        double bias[NCH];
        for(int j=0; j<NCH; j++){

            bias[j]=0;

            for(int i=0; i<VSIZE;i++)
                bias[j]+=timeData[j][i+(cnt*VSIZE)];

            bias[j]/=VSIZE;

            for(int i=0; i<VSIZE;i++)
                timeData[j][i+(cnt*VSIZE)]-=bias[j];
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
        calculateFFT();
        update();

    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    chart.drawLinearGrid(painter, centralWidget()->geometry());

    painter.setRenderHint(QPainter::Antialiasing, true);
    // painter.setCompositionMode(QPainter::CompositionMode_HardLight);

    if(ui->radioCh_1->isChecked())
        chart.drawLinearData(painter, timeData[0], chart.plotColors[0]);
    if(ui->radioCh_2->isChecked())
        chart.drawLinearData(painter, timeData[1], chart.plotColors[1]);
    if(ui->radioCh_3->isChecked())
        chart.drawLinearData(painter, timeData[2], chart.plotColors[2]);
    if(ui->radioCh_4->isChecked())
        chart.drawLinearData(painter, timeData[3], chart.plotColors[3]);
    if(ui->radioCh_5->isChecked())
        chart.drawLinearData(painter, timeData[4], chart.plotColors[4]);
    if(ui->radioCh_6->isChecked())
        chart.drawLinearData(painter, timeData[5], chart.plotColors[5]);
    if(ui->radioCh_7->isChecked())
        chart.drawLinearData(painter, timeData[6], chart.plotColors[6]);
    if(ui->radioCh_8->isChecked())
        chart.drawLinearData(painter, timeData[7], chart.plotColors[7]);


    //        chart.drawLogGrid(painter, centralWidget()->geometry());
    //        chart.drawLogData(painter, magnitudeData);
}

void MainWindow::calculateFFT()
{
    for(int i=0;i<FFT_SIZE; i++){

        fftData[static_cast<uint>(i)].real(timeData[0][i]*fftWin[i]);
        fftData[static_cast<uint>(i)].imag(0);
    }

#if ARMADILLO_FFT
    fftData=arma::fft(fftData);
#else
    Fft::transform(fftData);
#endif

    for(int i=0;i<FFT_SIZE/2; i++){

        magnitudeData[i]=abs(fftData[static_cast<uint>(i)])*1;
        phaseData[i]=arg(fftData[static_cast<uint>(i)]);
    }

    double max=*std::max_element(magnitudeData.begin(), magnitudeData.end());
    for(int i=0;i<FFT_SIZE/2; i++){

        if(max>0)
            magnitudeData[i]/=max;  //normalise
        magnitudeData[i]+=0.01; //saturate -40 dB
    }
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
    QString FileName;
    FileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home", tr("Data (*.dat)"));
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    //file.read(reinterpret_cast<char*>(timeData[0].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));

    for(int j=0; j<NCH; j++)
        file.read(reinterpret_cast<char*>(timeData[j].data()), static_cast<uint>(VSIZE*FRCNT*sizeof(double)));
    file.close();




    //    QString FileName;
    //    FileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home", tr("Data (*.wav)"));
    //    QFile file(FileName);
    //    if (!file.open(QIODevice::ReadOnly))
    //        return;



    //   // qDebug()<< file.size();

    //    WaveHeaderEx waveHdr1, waveHdr2;



    //    //waveSignal.resize((file.size()-sizeof(waveHdr2))/sizeof(short));
    //    //waveSignal.fill(0);
    //    file.read(reinterpret_cast<char*>(&waveHdr2), static_cast<uint>(sizeof(waveHdr2)));
    //    //file.read(reinterpret_cast<char*>(waveSignal.data()), static_cast<uint>(waveSignal.size()*sizeof(short)));
    //    file.close();

    //    qDebug()<<"Channels"<<waveHdr2.Channels;
    //    qDebug()<<"dwSampleLength"<<waveHdr2.dwSampleLength;
    //    qDebug()<<"DataLength"<<waveHdr2.DataLength;
    //    qDebug()<<waveSignal.size();


    //    CreateWaveHeader(waveHdr1, NCH, 96000,  static_cast<uint>(waveSignal.size()*sizeof(short)/NCH));

    update();
}

void MainWindow::on_actionSave_triggered()
{
    QString FileName;
    //FileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home", tr("Data (*.dat)"));
    FileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home", tr("Data (*.wav)"));
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


}
