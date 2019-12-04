#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>
#include "lib/wavfilereader.h"
#include "lib/wavefilewriter.h"
#include <qprocess.h>
#include <qdir.h>

#include "pre_headers.h"
#include "lib/filesFunctions.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread, SIGNAL(tick()), this, SLOT(externalThread_tick()));
    connect(ui->actionRun,  SIGNAL(triggered()), this, SLOT(sendCommand()));
    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->actionBar,  SIGNAL(triggered()), this, SLOT(update()));

    timeData.resize(NCH);
    for(int i=0; i< timeData.size();i++){

        timeData[i].resize(DSIZE2);
        timeData[i].fill(0);
    }

    meanData.resize(NCH);
    meanData.fill(0.0);

//    wavData.resize(NCH);
//    for (int k = 0; k < NCH; k++){
//        wavData[k].resize(DSIZE2);
//        wavData[k].fill(0.0);
//    }

    waveBin.resize(sizeof (float)*DSIZE);

    ui->statusBar->showMessage("No device");
    QString portname;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if(info.serialNumber()=="NXP-77"){

            portname=info.portName();
            serial.setPortName(portname);
            if (serial.open(QIODevice::ReadWrite)) {

                //serial.setBaudRate( serial.Baud115200,  serial.AllDirections);
                ui->statusBar->showMessage(tr("Device: %1").arg(info.serialNumber()));
                serial.clear();
                thread.start(thread.HighestPriority);

            }
            else
            {
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

    // Output WAVE settings
    format.setCodec("audio/pcm");
    format.setSampleRate(DSIZE2*2);                           // Hz sample per second
    format.setChannelCount(NCH);
    format.setSampleSize(sizeof( float )*8);                // sizeof(float) => 4 bytes ( multiplayng by 8 to get valid 32 bits)
    qDebug() << "SampleSize" << sizeof( float )*8;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SampleType::Float);

    wav_out = new WaveFileWriter(nullptr);
    ui->lineEdit_path->setText( get_unique_filename( ui->lineEdit_path->text() ));

//    ui->checkBoxClipboard->hide();
    coutingDownToZero = 0;
    trySave = false;

    qDebug()<<std::numeric_limits<uint16_t>::max();
    qDebug()<<std::numeric_limits<int16_t>::max();
}

MainWindow::~MainWindow()
{
    if (wav_out->isOpen()) {
        wav_out->close();
    }
    thread.terminate();
    thread.wait();
    serial.close();
    delete wav_out;
    delete ui;
}

// ------------------------------------------------------------------------------

void MainWindow::externalThread_tick()
{


    auto_actionRun_serial_port(3);

    // qDebug()<<serial.size();
    if(!ui->actionRun->isChecked())
        serial.clear();

    if (serial.size() >= DSIZE){

//        qDebug()<<serial.size();
//        readdata=serial.readd(DSIZE);
        readdata=serial.readAll();

        uint16_t *sample=reinterpret_cast<uint16_t*>(readdata.data());
        int16_t  *pDsc=reinterpret_cast<int16_t*>(waveBin.data());

        for(int i=0; i<DSIZE2;i++){

            for(int j=0; j<NCH; j++) {
                *pDsc++ = static_cast<int16_t>((*sample) - (65535+1)/2);
                timeData[j][i]=(*sample++)/65535.0;

            }
        }
        if ( coutingDownToZero ) { // saveing_sample_counter
//                    saveWave();
            qDebug() << "count" << coutingDownToZero;
            if ( coutingDownToZero-- >= 0 )
            {
                ui->progressBar->setValue( ui->spinBox->value() - coutingDownToZero);
                //    qDebug() << "to zero count:" << coutingDownToZero;
            }
        }
        if ( coutingDownToZero )
            wav_out->write(waveBin.data(), DSIZE);

        if (coutingDownToZero == 0)
        {
            wav_out->close();
        }

        for(int j=0; j<NCH; j++)
            meanData[j] = std::accumulate( timeData[j].begin(), timeData[j].end(), 0.0)/timeData[j].size();

        update();

        if(ui->actionRun->isChecked())
            sendCommand();
    }
}

// ------------------------------------------------------------------------------

void MainWindow::sendCommand()
{
    senddata.clear();
    senddata[0]=static_cast<char>(128+(ui->actionTrigger->isChecked()<<6));
    senddata[1]=static_cast<char>(0);
    senddata[2]=static_cast<char>(0);
    senddata[3]=static_cast<char>(0); // ui->pwmValue3->value()
    serial.write(senddata);
}

// ------------------------------------------------------------------------------

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    chart.drawLinearGrid(painter, centralWidget()->geometry());

//    for (int i = 0; i < DSIZE2; i++)
//    {
//        timeData[0][i] += 0.2;
////        timeData[1][i] += 0.0;
//        timeData[2][i] -= 0.2;
//    }

    if(ui->actionLine->isChecked()){

        if(ui->selectInput1->isChecked()){

            chart.plotColor=Qt::red;
            chart.drawLinearData(painter, timeData[0]);
        }
        if(ui->selectInput2->isChecked()){

            chart.plotColor=Qt::green;
            chart.drawLinearData(painter, timeData[1]);
        }
        if(ui->selectInput3->isChecked()){

            chart.plotColor=Qt::yellow;
            chart.drawLinearData(painter, timeData[2]);
        }
    }

    if(ui->actionBar->isChecked()){

        chart.plotColor=Qt::cyan;
        chart.drawBarsData(painter, meanData);
    }

    QPen pen;
    QFont font;
    font.setPointSize(8);
    pen.setWidth(1);
    pen.setColor(Qt::white);
    painter.setPen(pen);

    //    int gx=geometry().x()+MX;
    //    int gy=geometry().y()+MY;
    int gw=geometry().width()-(2*MX);
    int gh=geometry().height()-(2*MY);

    painter.drawText(QPointF(geometry().width()/2-(font.pointSize()), gh+40+(font.pointSize())),
                     QString().sprintf("%s","Time [ms]"));

    if (!serial.isOpen()) {
        if ( trySave )
        {
            pen.setColor(Qt::red);
            painter.setPen(pen);
            update();
        }
        painter.drawText(QPointF(gw/3+(font.pointSize())+5,50+(font.pointSize())),
                         QString().sprintf("%s","Nie nawiązano połączenia, spróbuj podłączyć płytkę i uruchomić program ponownie"));
    }
    //    if ( coutingDownToZero ) {
    ////        chart.plotColor = Qt::darkRed;
    //        int px = MX - 5;
    //        int shift = px/3*2;
    //        painter.drawRoundedRect(gw+shift*2-1, px+shift+1, px, px, px, px);
    //    }
}

// ------------------------------------------------------------------------------

void MainWindow::auto_actionRun_serial_port(int try_times)
{
    static int waiter(0);

    if( waiter >= 0 )
    {
        if(!ui->actionRun->isChecked())
        {
            if( waiter <= try_times ) {
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
// ------------------------------------------------------------------------------

void MainWindow::saveWave()
{
//    qDebug() << "count" << coutingDownToZero;
//    if ( coutingDownToZero-- >= 0 )
//    {
//        ui->progressBar->setValue( ui->spinBox->value() - coutingDownToZero);
//        //    qDebug() << "to zero count:" << coutingDownToZero;
//    }

//    double *pSrc = nullptr;
//    float *pDsc = nullptr;

//    pDsc = reinterpret_cast<float*>(waveBin.data());
//    for(int i=0; i<DSIZE2;i++){

//        for(int j=0; j<NCH; j++)
//            (*pDsc++) = (float)(timeData[j][i]);
//    }

//    for (int i = 0; i < DSIZE2; i++)
//    {

////        pSrc = timeData[k].data();
////        pDsc = static_cast<float*>(wavData[k].data());

//        for (int k = 0; k < NCH; k++)
//        {
//            *pDsc++ = timeData[k][i];
//        }
////        wavData[k][1] = k;

////        wav_out->write(reinterpret_cast<char*>(wavData[k].data()), static_cast<uint>(wavData[k].size())*sizeof(wavData[0][0]));

////        qInfo() <<"zapisano kanał "<<  k << "size(): " << wavData[k].size()*sizeof (wavData[0][0]) << "time:" << QDateTime::currentMSecsSinceEpoch();
//    }

}

// ------------------------------------------------------------------------------

void MainWindow::on_pushButton_enter_clicked()
{
    trySave = true;
    QString uniqName = get_unique_filename( ui->lineEdit_path->text() );
    QFileInfo fi(uniqName);                                              // object to get only fileName against path
    QDir dir;// We create the directory if needed

    ui->lineEdit_path->setText( fi.filePath() );
    ui->progressBar->setRange(0, ui->spinBox->value());
    ui->progressBar->setValue(0);
    wav_out->close();

    if (!dir.exists(fi.path() )) {
        dir.mkpath( fi.path() ); // You can check the success if needed
    }

    wav_out->open(  ui->lineEdit_path->text(), format );
    ui->spinBox->setStepType(QAbstractSpinBox::StepType::AdaptiveDecimalStepType);
    coutingDownToZero = ui->spinBox->value();

    if ( !wav_out->isOpen() ) {
        ui->statusBar->showMessage("Error open: " + wav_out->fileName() );
    }

//    ui->progressBar->setValue( ui->spinBox->value() );

    if( ui->checkBoxClipboard->isChecked() )
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText( ui->lineEdit_path->text()+ "/" +ui->lineEdit_path->text() );
    }
}

// ------------------------------------------------------------------------------

void MainWindow::on_pushButton_return_clicked()
{
    ui->pushButton_enter->animateClick();
}

// ------------------------------------------------------------------------------

void MainWindow::on_commandLinkButton_show_clicked()
{
    showFileInFolder(ui->lineEdit_path->text());
}

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
