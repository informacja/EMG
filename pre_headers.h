#ifndef PRE_HEADERS_H
#define PRE_HEADERS_H

#include <QApplication>
// chart.h
#include <QPainter>
#include <math.h>
//#include <vector>
//mainwindow.h
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include <math.h>
#include "thread.h"
#include "chart.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
//#include "kissfft-131/kiss_fft.h"
#include <QMimeData>
#include <QDragEnterEvent>
#include <QFileInfo>
#include <QFileDialog>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSplitter>

// ui_mainwindow.h

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

enum{
    SIMULATION_NO = 0,
    SIMULATION_BINARY,
    SIMULATION_CSV
};

#endif // PRE_HEADERS_H
