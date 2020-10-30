#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include "chart.h"
#include "wave.h"

#define ARMADILLO_FFT 1

#if ARMADILLO_FFT
#include <armadillo>
#else
#include "FftComplex.h"
#endif



#define DSIZE    4096
#define NCH 8
#define FS 2048
#define DSIZE2   (DSIZE/2)

#define VSIZE (DSIZE2/NCH)      // 256
#define SECONDS 5               // of recording
#define FRCNT NCH*SECONDS       // 8 chanels, 5 seconds

#define FFT_SIZE VSIZE*FRCNT

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
    void sendCommand();
    void readData();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void calculateFFT();
    void filterData();

    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
    QVector<QVector<double> > timeData;
    QVector<double> magnitudeData;
    QVector<double> phaseData;
    QVector<double> fftWin;

    QVector<short> waveSignal;

    uint32_t cnt;

#if ARMADILLO_FFT
    arma::cx_vec fftData;
#else
    std::vector<std::complex<double> >fftData;
#endif

    Chart chart;

};

#endif // MAINWINDOW_H
