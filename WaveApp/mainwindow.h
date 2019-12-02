#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include "thread.h"
#include "chart.h"
#include "pre_headers.h"

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
    void auto_actionRun_serial_port(int try_times);
    void saveWave();
    void on_pushButton_enter_clicked();
    void on_pushButton_return_clicked();
    void on_commandLinkButton_show_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    Thread thread;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
//    QVector<double> timeDataCh1, timeDataCh2, timeDataCh3;
    QVector<QVector<double> > timeData;
    QVector<double> meanData;

    Chart chart;
    QAudioFormat format;
    int coutingDownToZero;
    WaveFileWriter* wav_out;
    QVector<QVector<float>> wavData;

};

#endif // MAINWINDOW_H
