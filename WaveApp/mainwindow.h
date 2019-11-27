#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include "thread.h"
#include "chart.h"

#define NCH 3
#define DSIZE    (NCH*2048)
#define DSIZE2   (DSIZE/2/NCH)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void externalThread_tick();
    void sendCommand();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);

    Thread thread;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
    QVector<double> timeDataCh1, timeDataCh2, timeDataCh3;
    QVector<QVector<double> > timeData;
    QVector<double> meanData;

    Chart chart;

};

#endif // MAINWINDOW_H
