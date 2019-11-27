#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>
#include "lib/wavfilereader.h"
#include "lib/wavefilewriter.h"
#include <qprocess.h>
#include <qdir.h>

#include "pre_headers.h"

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


//    wav_out = new WaveFileWriter(nullptr);
}

MainWindow::~MainWindow()
{
    thread.terminate();
    thread.wait();
    serial.close();
    delete ui;
}

void MainWindow::externalThread_tick()
{

    auto_actionRun_serial_port(3);

    // qDebug()<<serial.size();
    if(!ui->actionRun->isChecked())
        serial.clear();

//    for (int i = 0; i < WSIZE; i++)
//    {
//        timeData[0][i] += 0.2;
//        timeData[1][i] += 0.45;
//        timeData[2][i] += 0.8;
//    }

    if (serial.size() >= DSIZE){

        //qDebug()<<serial.size();
        readdata=serial.read(DSIZE);

        uint16_t *sample=reinterpret_cast<uint16_t*>(readdata.data());
        for(int i=0; i<DSIZE2;i++){

            for(int j=0; j<NCH; j++)
                timeData[j][i]=(*sample++)/65535.0;
        }

        for(int j=0; j<NCH; j++)
            meanData[j] = std::accumulate( timeData[j].begin(), timeData[j].end(), 0.0)/timeData[j].size();

        update();

        if(ui->actionRun->isChecked())
            sendCommand();
    }
}

void MainWindow::sendCommand()
{
    senddata.clear();
    senddata[0]=static_cast<char>(128+(ui->actionTrigger->isChecked()<<6));
    senddata[1]=static_cast<char>(0);
    senddata[2]=static_cast<char>(0);
    senddata[3]=static_cast<char>(0); // ui->pwmValue3->value()
    serial.write(senddata);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    chart.drawLinearGrid(painter, centralWidget()->geometry());

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
// ------------------------------------------------------------------------------


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
  QVector<QVector<float>> wavData;

  wavData.resize(NCH);
  for (int k = 0; k < NCH; k++)
    wavData[k].resize(DSIZE2);

  if ( coutingDownToZero-- >= 0 )
  {
    ui->progressBar->setValue( ui->spinBox->value() - coutingDownToZero);
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

        wav_out->write(reinterpret_cast<char*>(wavData[k].data()), static_cast<uint>(wavData[k].size())*sizeof(wavData[0][0]));

        qInfo() <<"zapisano kanał "<<  k << "size(): " << wavData[k].size()*sizeof (wavData[0][0]) <<  QDateTime::currentMSecsSinceEpoch();

   }
}



void MainWindow::on_pushButton_enter_clicked()
{

//    QString uniqName = get_unique_filename(path+ "/" + ui->lineEdit_fileN->text() );
//    QFileInfo fi(uniqName);
//    ui->lineEdit_fileN->setText( fi.fileName() );
    //TO DO
    QString fName = "";

    ui->progressBar->setRange(0, ui->spinBox->value());
    ui->progressBar->setValue(0);

//      wav_out->close();
//      if ( ui->lineEdit_path->text().isEmpty() )
//          fName = ui->lineEdit_path->text();
//      else
//      {
//        QDir dir;// We create the directory if needed
//        if (!dir.exists(ui->lineEdit_path->text()))
//            dir.mkpath(ui->lineEdit_path->text()); // You can check the success if needed

//          fName = lineEdit_path;
//      }
//      QFileInfo fi( get_unique_filename(fName) );
//      ui->lineEdit_fileN->setText( fi.completeBaseName()+ "." +fi.completeSuffix() );

//      fName = ui->lineEdit_path->text()+ "/" +ui->lineEdit_fileN->text();
//      wav_out->open( fName, format );
//      coutingDownToZero =  ui->spinBox_nDataPerFile->value();
//      qDebug() << "is open wav" << wav_out->isOpen() << wav_out->fileName();
//      ui->progressBar->setValue(100);

//      if( ui->checkBox_autoCpyPath->isChecked() )
//      {
//          QClipboard *clipboard = QGuiApplication::clipboard();
//          clipboard->setText( ui->lineEdit_path->text()+ "/" +ui->lineEdit_fileN->text() );
//      }
}

void MainWindow::on_pushButton_return_clicked()
{
     ui->pushButton_enter->animateClick();
}

void MainWindow::on_commandLinkButton_clicked()
{
    QString path = QDir::currentPath()+ "/" +ui->lineEdit_path->text()+ "/" +ui->lineEdit_path->text() ;
    showFileInFolder(path);
}
