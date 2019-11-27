#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread, SIGNAL(tick()), this, SLOT(externalThread_tick()));
    connect(ui->actionRun,  SIGNAL(triggered()), this, SLOT(sendCommand()));
    connect(ui->actionLine, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->actionBar,  SIGNAL(triggered()), this, SLOT(update()));

    //            timeDataCh1.resize(DSIZE2);
    //            timeDataCh2.resize(DSIZE2);
    //            timeDataCh3.resize(DSIZE2);
    //            timeDataCh1.fill(0);
    //            timeDataCh2.fill(0);
    //            timeDataCh3.fill(0);

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
    // qDebug()<<serial.size();
    if(!ui->actionRun->isChecked())
        serial.clear();

    if (serial.size() >= DSIZE){

        //qDebug()<<serial.size();
        readdata=serial.readAll();

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


