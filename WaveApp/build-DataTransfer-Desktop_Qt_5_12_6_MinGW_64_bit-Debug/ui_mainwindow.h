/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRun;
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuacquisition;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGroupBox *groupBox;
    QRadioButton *radioCh_1;
    QRadioButton *radioCh_2;
    QRadioButton *radioCh_3;
    QRadioButton *radioCh_4;
    QRadioButton *radioCh_5;
    QRadioButton *radioCh_6;
    QRadioButton *radioCh_7;
    QRadioButton *radioCh_8;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 410);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setIconSize(QSize(24, 24));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        actionRun->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuacquisition = new QMenu(menuBar);
        menuacquisition->setObjectName(QString::fromUtf8("menuacquisition"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setMinimumSize(QSize(105, 44));
        dockWidget->setMaximumSize(QSize(105, 524287));
        dockWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 64, 64);\n"
"color: rgb(255, 255, 255);"));
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(12, 0, 80, 291));
        radioCh_1 = new QRadioButton(groupBox);
        radioCh_1->setObjectName(QString::fromUtf8("radioCh_1"));
        radioCh_1->setGeometry(QRect(10, 40, 61, 20));
        radioCh_1->setChecked(true);
        radioCh_1->setAutoExclusive(false);
        radioCh_2 = new QRadioButton(groupBox);
        radioCh_2->setObjectName(QString::fromUtf8("radioCh_2"));
        radioCh_2->setGeometry(QRect(10, 70, 61, 20));
        radioCh_2->setChecked(true);
        radioCh_2->setAutoExclusive(false);
        radioCh_3 = new QRadioButton(groupBox);
        radioCh_3->setObjectName(QString::fromUtf8("radioCh_3"));
        radioCh_3->setGeometry(QRect(10, 100, 61, 20));
        radioCh_3->setChecked(true);
        radioCh_3->setAutoExclusive(false);
        radioCh_4 = new QRadioButton(groupBox);
        radioCh_4->setObjectName(QString::fromUtf8("radioCh_4"));
        radioCh_4->setGeometry(QRect(10, 130, 61, 20));
        radioCh_4->setChecked(true);
        radioCh_4->setAutoExclusive(false);
        radioCh_5 = new QRadioButton(groupBox);
        radioCh_5->setObjectName(QString::fromUtf8("radioCh_5"));
        radioCh_5->setGeometry(QRect(10, 160, 61, 20));
        radioCh_5->setChecked(true);
        radioCh_5->setAutoExclusive(false);
        radioCh_6 = new QRadioButton(groupBox);
        radioCh_6->setObjectName(QString::fromUtf8("radioCh_6"));
        radioCh_6->setGeometry(QRect(10, 190, 61, 20));
        radioCh_6->setChecked(true);
        radioCh_6->setAutoExclusive(false);
        radioCh_7 = new QRadioButton(groupBox);
        radioCh_7->setObjectName(QString::fromUtf8("radioCh_7"));
        radioCh_7->setGeometry(QRect(10, 220, 61, 20));
        radioCh_7->setChecked(true);
        radioCh_7->setAutoExclusive(false);
        radioCh_8 = new QRadioButton(groupBox);
        radioCh_8->setObjectName(QString::fromUtf8("radioCh_8"));
        radioCh_8->setGeometry(QRect(10, 250, 61, 20));
        radioCh_8->setChecked(true);
        radioCh_8->setAutoExclusive(false);
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuacquisition->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuacquisition->addAction(actionRun);
        mainToolBar->addAction(actionRun);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EMG Analyzer", nullptr));
        actionRun->setText(QApplication::translate("MainWindow", "Run", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuacquisition->setTitle(QApplication::translate("MainWindow", "Acquisition", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Channel", nullptr));
        radioCh_1->setText(QApplication::translate("MainWindow", "Ch 1", nullptr));
        radioCh_2->setText(QApplication::translate("MainWindow", "Ch 2", nullptr));
        radioCh_3->setText(QApplication::translate("MainWindow", "Ch 3", nullptr));
        radioCh_4->setText(QApplication::translate("MainWindow", "Ch 4", nullptr));
        radioCh_5->setText(QApplication::translate("MainWindow", "Ch 5", nullptr));
        radioCh_6->setText(QApplication::translate("MainWindow", "Ch 6", nullptr));
        radioCh_7->setText(QApplication::translate("MainWindow", "Ch 7", nullptr));
        radioCh_8->setText(QApplication::translate("MainWindow", "Ch 8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
