#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pre_headers.h"
#include "kissfft-131/kiss_fft.h"
#include "iir/Iir.h"


#define FS          8000 // dla procesora M33 z ostatnich zajęć tydzień temu
#define DSIZE       8192


//#define DSIZE    4096
#define NCH 8
//#define FS 2048
#define QLV_BYTES_PER_WORD 2   // uint16 // Quantisation LeVel, number of bytes per variable. Scale factor
#define DSIZE2   (DSIZE/QLV_BYTES_PER_WORD)
#define WSIZE    (DSIZE2/2)                   // window length

#define VSIZE (DSIZE2/NCH)      // 256
#define SECONDS 5               // of recording
#define FRCNT NCH*SECONDS       // 8 chanels, 5 seconds

#define FFT_SIZE VSIZE*FRCNT

//#define NCH 3
//#define TEMP_NCH 8
//#define DSIZE    (NCH*2048)
//#define DSIZE2   (DSIZE/2/NCH)                // number of samples per chanel (uint16_t)
//#define WSIZE    (DSIZE2/2)                   // window length
#define BUF_LEN   10e6
#define NBARS     32                          // to divide  WSIZE
#define ORDER     (2)

// TO DO: Fir
// adaptacyjny
//pętla pll
//do 5mV
//10-400hz
// podskórne do 1KHz

#define FPS FPS
//#define DATA_DIR "./data/"
#define FILE_NAME  "out"
#define EXT        ".wav"
#define MATLAB      "../matlab"
#define SAMPLE_DIR  MATLAB "/sample"
#define GEN_DIR     MATLAB "/generated"
#define CSV_LOG     MATLAB "/log.csv"

//#define B_SIZE DSIZE                          // minimalny rozmiar wczytywaniej paczki danych z pliku
#define SQUARE(a) (a*a)
#define INI_FILES "Ini_Files"
//#define ALLOW_USE_FILTERS

#define DISABLE_FILTERS_ON_STARTUP

namespace Ui {
    class MainWindow;
}

class FPS : public QWidget
{
public:
    QTime m_time;
    int m_frameCount;

 FPS()  { m_frameCount = 0;}

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
};

// -----------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void externalThread_tick();
    void sendCommand();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionOtw_rz_triggered(bool checked);
    void on_actionZapisz_domy_lne_triggered();
    void on_actionKatalog_triggered();
    void on_pushButto_kat_clicked();
    void on_radio_saveAllDir_clicked();
    void on_radio_handOpen_clicked();
    void on_radio_handClose_clicked();
    void on_pushButton_openFile_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_toolButton_return_clicked();
    void on_toolButton_enter_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    void alloc_memory_sub_constructor();
    void pointers_set_null();
    inline void auto_actionRun_serial_port(int count_up_to = 100);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void save_to_file( bool wait_mseconds_0 = 0);
    bool simulation_open_file(  QString fileName );
    void saveSettings( const QVariant &value = FILE_NAME EXT, const QString &key = "path", const QString &group = INI_FILES);
    QVariant loadSettings(const QString &key = "path", const QString &group = INI_FILES, const QVariant &defaultValue = QVariant());
    qint64 simulation_read_data_from_file();
    void draw_bars_Hz_gap(int window_length, int);
    void alloc_files();
    Simulation_Type find_source_file(QString filename_or_prefered_extension = "" );    
    QString get_unique_filename(QString filename, bool allow_empty = true);
    void load_data_from_serialport();
    void process_signals();
    void load_timeData_from_wav_file();    
    void generate_3_signals(int speed, int gap, bool mirror, bool fillHalf );
    void apply_filters();    
    void signal_source();

Q_SIGNALS:
signals:
    void simulation_changed(Simulation_Type);

public slots:
    void set_simulation_info(const Simulation_Type &newSimul);
    void set_butterworth_BandStop_fq(int cutoff_frequency);
    void set_butterworth_BandStop_width(int width);
    void set_butterworth_HiPass(int cutoff_frequency);
    void set_lineEdit_qnique_filename(QString path);
    void simulation_adjust(Simulation_Type);

private:
    Thread thread;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata, buff;
    QVector<QVector<double>> timeData;                                          // calc and display
    QVector<double> meanData;
    QVector<QVector<double>> spectrums;                                          // resized to NCH in constructor
    Chart chart;

    // Added
    kiss_fft_cfg cfg;
    int isinverse;                                                  // fft needed
    kiss_fft_cpx* input[NCH];
    kiss_fft_cpx* out[NCH];
    kiss_fft_cpx test[DSIZE2];

    kiss_fft_scalar *hamming, *hann;                                   // okno, tak naprawdę typ kiss_fft_scalar to float :D
    Iir::Butterworth::HighPass<ORDER> fHiPass;
    Iir::Butterworth::BandStop<ORDER> fBandStop;

    QFile file_csv;                                             // read and write
    QTextStream stream;                                         // for csv read and write;
    Simulation_Type simulation;
    FPS fps;
    WavFilerReader* fileWaveIn;                                     // input or output
    WaveFileWriter* fileWaveOut;
    QAudioFormat format;
    int coutingDownToZero;
    bool wait_for_data = true;

//    QBasicTimer m_timer;
    double fi[3];

//    void paintEvent(QPaintEvent * p) {
//       QPainter painter(this);
//       // WARNING: this method can be called at any time
//       // If you're basing animations on passage of time,
//       // use a QElapsedTimer to find out how much time has
//       // passed since the last repaint, and advance the animation
//       // based on that.
//       ...
//       for(int i=0; i<10;i++)
//       {
//          method(m_circles[i]); //co-ordinates change
//          m_circles[i].paint(&painter);
//       }
//       ...
//     }

//    void timerEvent(QTimerEvent * ev) {
//       if (ev->timerId() != m_timer.timerId()) {
//         QWidget::timerEvent(ev);
//         return;
//       }
//       update();
//     }

};

#endif // MAINWINDOW_H
