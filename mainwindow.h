#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pre_headers.h"

#include "kissfft-131/kiss_fft.h"
#define NCH 3
#define DSIZE    (NCH*2048)
#define DSIZE2   (DSIZE/2/NCH)
#define NBARS     32                          // do dzielenia DSIZE2

//#define DISABLE_INPUT_3                     // Added by Piotr, don't display unused
#define DEBUG_FILE  "out"
#define EXT ".bin"
#define B_SIZE DSIZE                          // minimalny rozmiar wczytywaniej paczki danych z pliku
#define SQUARE(a) (a*a)
//#define SOFT_NAME       "EMG"
#define INI_FILES "Ini_Files"

namespace Ui {
class MainWindow;
}

class FPS : public QWidget
{

public:
FPS() : m_frameCount(0) {}

void paintEvent(QPaintEvent *e) {
    if (m_frameCount == 0) {
         m_time.start();
    } else {
//        printf("FPS is %f ms\n", m_time.elapsed() / float(m_frameCount));
        qWarning() << "FPS is " << (m_frameCount / (float(m_time.elapsed()) / 1000.0f)) << endl;

    }
    m_frameCount++;

    // Painting goes here...

}

QTime m_time;
int m_frameCount;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void externalThread_tick();
    void sendCommand();
    void on_textEdit_textChanged();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionOtw_rz_triggered(bool checked);
    void on_actionZapisz_domy_lne_triggered();
    void on_actionKatalog_triggered();
    void on_textEdit_cursorPositionChanged();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void Alloc_memory_sub_constructor();
    inline void auto_actionRun_serial_port(int count_up_to = 100);
    bool load_data(bool sav_add_seconds = false, int read_wait_milisec = 100);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void save_to_file( bool wait_mseconds_0 = 0);
    bool simulation_open_file(  QString fileName );
    void saveSettings( const QVariant &value = DEBUG_FILE EXT, const QString &key = "path", const QString &group = INI_FILES);
    QVariant loadSettings(const QString &key = "path", const QString &group = INI_FILES, const QVariant &defaultValue = QVariant());
    bool simulation_read_data_from_file();
    void draw_bars_Hz_gap(int window_length, int);


    Thread thread;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
    QVector<double> timeDataCh1, timeDataCh2, timeDataCh3;
    QVector<QVector<double> > timeData;
    QVector<double> meanData;
    QVector<QVector<double> > spectrum;                                         // resized to NCH in constructor
    Chart chart;

    // Added
    kiss_fft_cfg cfg;
    int isinverse;
    kiss_fft_cpx * in[NCH];
    kiss_fft_cpx * out[NCH];
    kiss_fft_cpx test[DSIZE2];


    kiss_fft_scalar *hamming;                                                   // okno, tak naprawdę typ to float :D
//    kiss_fft_scalar *tbuf = NULL; // TO DO

    QFile file_in, file_out, file_csv;
    QTextStream stream;    

    int simulation;
    FPS fps;

};




#endif // MAINWINDOW_H
