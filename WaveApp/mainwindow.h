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
#define QLV_BYTES_PER_WORD 2   // uint16 // Quantisation LeVel, number of bytes per variable. Scale factor
#define DSIZE2   (DSIZE/QLV_BYTES_PER_WORD)

#define VSIZE (DSIZE2/NCH)      // Vector
#define SECONDS 5               // of recording
#define FRCNT NCH*SECONDS       // 8 chanels, 5 seconds

#define FFT_SIZE VSIZE*FRCNT
//#define FFT_SIZE ((VSIZE*FRCNT)/SECONDS) // one second

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

    void on_pushButton_clicked();

    void on_textEditFeatures_textChanged();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void loadFile( QString fileName );


    void on_actionMaximize_triggered();

    void on_pushButtonMac_clicked();

    void on_checkBoxARMA_stateChanged(int arg1);


    void on_groupBox_clicked();

    void on_checkBoxVirtualSpace_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void calculateFFT(int cnt);
    void filterData();
    void virtualSeparate();

    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
    QVector<QVector<double>> timeData;    
    QVector<QVector<double>> timeDataView;
    QVector<QVector<double>> magnitudeData;
    QVector<QVector<double>> phaseData;
    QVector<double> fftWin;
    QVector<int> gestureNrList;

    QVector<short> waveSignal;

    uint32_t cnt;
    QVector<int> gestureNr;

#if ARMADILLO_FFT
    arma::cx_vec fftData;
#else
    std::vector<std::complex<double> >fftData;
#endif

    Chart chart;

};

#endif // MAINWINDOW_H
