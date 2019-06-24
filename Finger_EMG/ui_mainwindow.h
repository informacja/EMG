/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRun;
    QAction *actionTrigger;
    QAction *actionLine;
    QAction *actionBar;
    QAction *actionSpektrum;
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionOtw_rz;
    QAction *actionZapisz_domy_lne;
    QAction *actionKatalog;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuUstwienia;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_config;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *selectInput2;
    QCheckBox *selectInput3;
    QCheckBox *selectInput1;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_3;
    QRadioButton *radioBtn_rect;
    QRadioButton *radioBtn_hann;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *pwmLabel2;
    QSlider *pwmValue1;
    QLabel *pwmLabel3;
    QSlider *verticalSlider;
    QSlider *pwmValue2;
    QSlider *pwmValue3;
    QLabel *pwmLabel1;
    QWidget *tab_save;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QRadioButton *radio_saveAllDir;
    QRadioButton *radio_handOpen;
    QRadioButton *radio_handClose;
    QPushButton *pushButto_kat;
    QTextEdit *tEdit_out;
    QProgressBar *progressBar;
    QToolButton *toolButton;
    QSpinBox *spinBox_save;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(725, 640);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setAcceptDrops(true);
        MainWindow->setIconSize(QSize(24, 24));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        actionRun->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon);
        actionTrigger = new QAction(MainWindow);
        actionTrigger->setObjectName(QString::fromUtf8("actionTrigger"));
        actionTrigger->setCheckable(true);
        actionTrigger->setChecked(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/trigger.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTrigger->setIcon(icon1);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QString::fromUtf8("actionLine"));
        actionLine->setCheckable(true);
        actionLine->setChecked(false);
        actionLine->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/lines.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine->setIcon(icon2);
        actionLine->setIconVisibleInMenu(true);
        actionBar = new QAction(MainWindow);
        actionBar->setObjectName(QString::fromUtf8("actionBar"));
        actionBar->setCheckable(true);
        actionBar->setChecked(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/bars.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBar->setIcon(icon3);
        actionSpektrum = new QAction(MainWindow);
        actionSpektrum->setObjectName(QString::fromUtf8("actionSpektrum"));
        actionSpektrum->setCheckable(true);
        actionSpektrum->setChecked(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/heartbeat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSpektrum->setIcon(icon4);
        actionSpektrum->setIconVisibleInMenu(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setCheckable(true);
        actionSave->setChecked(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon5);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOtw_rz = new QAction(MainWindow);
        actionOtw_rz->setObjectName(QString::fromUtf8("actionOtw_rz"));
#ifndef QT_NO_TOOLTIP
        actionOtw_rz->setToolTip(QString::fromUtf8("Otw\303\263rz"));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionOtw_rz->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionOtw_rz->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
        actionOtw_rz->setAutoRepeat(false);
        actionZapisz_domy_lne = new QAction(MainWindow);
        actionZapisz_domy_lne->setObjectName(QString::fromUtf8("actionZapisz_domy_lne"));
        actionKatalog = new QAction(MainWindow);
        actionKatalog->setObjectName(QString::fromUtf8("actionKatalog"));
        actionKatalog->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 725, 20));
#ifndef QT_NO_TOOLTIP
        menuBar->setToolTip(QString::fromUtf8("sdf"));
#endif // QT_NO_TOOLTIP
        menuBar->setToolTipDuration(44);
#ifndef QT_NO_STATUSTIP
        menuBar->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
        menuUstwienia = new QMenu(menuBar);
        menuUstwienia->setObjectName(QString::fromUtf8("menuUstwienia"));
        menuUstwienia->setMouseTracking(false);
        menuUstwienia->setAcceptDrops(false);
#ifndef QT_NO_TOOLTIP
        menuUstwienia->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        menuUstwienia->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setAcceptDrops(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setAutoFillBackground(true);
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(171, 400));
        dockWidget->setMaximumSize(QSize(171, 524287));
        dockWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 64, 64);\n"
"color: rgb(255, 255, 255);"));
        dockWidget->setFloating(false);
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 150));
        tab_config = new QWidget();
        tab_config->setObjectName(QString::fromUtf8("tab_config"));
        groupBox = new QGroupBox(tab_config);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 131, 60));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        selectInput2 = new QCheckBox(groupBox);
        selectInput2->setObjectName(QString::fromUtf8("selectInput2"));
        selectInput2->setChecked(false);
        selectInput2->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput2, 0, 1, 1, 1);

        selectInput3 = new QCheckBox(groupBox);
        selectInput3->setObjectName(QString::fromUtf8("selectInput3"));
        selectInput3->setChecked(true);
        selectInput3->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput3, 0, 2, 1, 1);

        selectInput1 = new QCheckBox(groupBox);
        selectInput1->setObjectName(QString::fromUtf8("selectInput1"));
        selectInput1->setChecked(true);
        selectInput1->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput1, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(tab_config);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 80, 121, 71));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMinimumSize(QSize(0, 40));
        radioBtn_rect = new QRadioButton(groupBox_3);
        radioBtn_rect->setObjectName(QString::fromUtf8("radioBtn_rect"));
        radioBtn_rect->setGeometry(QRect(10, 20, 84, 19));
        radioBtn_rect->setChecked(true);
        radioBtn_hann = new QRadioButton(groupBox_3);
        radioBtn_hann->setObjectName(QString::fromUtf8("radioBtn_hann"));
        radioBtn_hann->setGeometry(QRect(10, 40, 51, 19));
        radioBtn_hann->setChecked(false);
        groupBox_2 = new QGroupBox(tab_config);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 160, 153, 171));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pwmLabel2 = new QLabel(groupBox_2);
        pwmLabel2->setObjectName(QString::fromUtf8("pwmLabel2"));
        pwmLabel2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel2, 0, 1, 1, 1);

        pwmValue1 = new QSlider(groupBox_2);
        pwmValue1->setObjectName(QString::fromUtf8("pwmValue1"));
        pwmValue1->setCursor(QCursor(Qt::PointingHandCursor));
        pwmValue1->setMouseTracking(false);
        pwmValue1->setFocusPolicy(Qt::WheelFocus);
        pwmValue1->setMinimum(1);
        pwmValue1->setMaximum(128);
        pwmValue1->setPageStep(10);
        pwmValue1->setSliderPosition(32);
        pwmValue1->setOrientation(Qt::Vertical);
        pwmValue1->setInvertedAppearance(false);
        pwmValue1->setInvertedControls(false);
        pwmValue1->setTickPosition(QSlider::TicksBothSides);

        gridLayout->addWidget(pwmValue1, 1, 0, 1, 1);

        pwmLabel3 = new QLabel(groupBox_2);
        pwmLabel3->setObjectName(QString::fromUtf8("pwmLabel3"));
        pwmLabel3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel3, 0, 2, 1, 1);

        verticalSlider = new QSlider(groupBox_2);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 1, 3, 1, 1);

        pwmValue2 = new QSlider(groupBox_2);
        pwmValue2->setObjectName(QString::fromUtf8("pwmValue2"));
        pwmValue2->setMaximum(100);
        pwmValue2->setOrientation(Qt::Vertical);
        pwmValue2->setTickPosition(QSlider::TicksBothSides);

        gridLayout->addWidget(pwmValue2, 1, 1, 1, 1);

        pwmValue3 = new QSlider(groupBox_2);
        pwmValue3->setObjectName(QString::fromUtf8("pwmValue3"));
        pwmValue3->setMaximum(100);
        pwmValue3->setOrientation(Qt::Vertical);
        pwmValue3->setTickPosition(QSlider::TicksBothSides);

        gridLayout->addWidget(pwmValue3, 1, 2, 1, 1);

        pwmLabel1 = new QLabel(groupBox_2);
        pwmLabel1->setObjectName(QString::fromUtf8("pwmLabel1"));
        pwmLabel1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel1, 0, 0, 1, 1);

        tabWidget->addTab(tab_config, QString());
        tab_save = new QWidget();
        tab_save->setObjectName(QString::fromUtf8("tab_save"));
        verticalLayout = new QVBoxLayout(tab_save);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(tab_save);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 90));
        radio_saveAllDir = new QRadioButton(groupBox_4);
        radio_saveAllDir->setObjectName(QString::fromUtf8("radio_saveAllDir"));
        radio_saveAllDir->setGeometry(QRect(10, 20, 84, 19));
        radio_handOpen = new QRadioButton(groupBox_4);
        radio_handOpen->setObjectName(QString::fromUtf8("radio_handOpen"));
        radio_handOpen->setGeometry(QRect(10, 40, 121, 19));
        radio_handClose = new QRadioButton(groupBox_4);
        radio_handClose->setObjectName(QString::fromUtf8("radio_handClose"));
        radio_handClose->setGeometry(QRect(10, 60, 101, 19));

        verticalLayout->addWidget(groupBox_4);

        pushButto_kat = new QPushButton(tab_save);
        pushButto_kat->setObjectName(QString::fromUtf8("pushButto_kat"));

        verticalLayout->addWidget(pushButto_kat);

        tEdit_out = new QTextEdit(tab_save);
        tEdit_out->setObjectName(QString::fromUtf8("tEdit_out"));
        tEdit_out->setEnabled(true);
        tEdit_out->setMaximumSize(QSize(16777215, 20));
        tEdit_out->setBaseSize(QSize(0, 10));
        tEdit_out->setAutoFillBackground(true);
        tEdit_out->setInputMethodHints(Qt::ImhNone);
        tEdit_out->setTabChangesFocus(false);
        tEdit_out->setLineWrapMode(QTextEdit::WidgetWidth);

        verticalLayout->addWidget(tEdit_out);

        progressBar = new QProgressBar(tab_save);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        toolButton = new QToolButton(tab_save);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../gettyimages-137225933-170667a.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon6);
        toolButton->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(toolButton);

        spinBox_save = new QSpinBox(tab_save);
        spinBox_save->setObjectName(QString::fromUtf8("spinBox_save"));
        spinBox_save->setMinimum(1);
        spinBox_save->setMaximum(1000);
        spinBox_save->setValue(10);

        verticalLayout->addWidget(spinBox_save);

        tabWidget->addTab(tab_save, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
#ifndef QT_NO_SHORTCUT
        pwmLabel2->setBuddy(pwmLabel2);
#endif // QT_NO_SHORTCUT

        menuBar->addAction(menuUstwienia->menuAction());
        menuUstwienia->addAction(actionOtw_rz);
        menuUstwienia->addAction(actionZapisz_domy_lne);
        menuUstwienia->addAction(actionKatalog);
        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionTrigger);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLine);
        mainToolBar->addAction(actionBar);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSpektrum);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionOpen);

        retranslateUi(MainWindow);
        QObject::connect(pwmValue1, SIGNAL(valueChanged(int)), pwmLabel1, SLOT(setNum(int)));
        QObject::connect(pwmValue2, SIGNAL(valueChanged(int)), pwmLabel2, SLOT(setNum(int)));
        QObject::connect(pwmValue3, SIGNAL(valueChanged(int)), pwmLabel3, SLOT(setNum(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PWM Controller", nullptr));
        actionRun->setText(QApplication::translate("MainWindow", "Run", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_NO_SHORTCUT
        actionTrigger->setText(QApplication::translate("MainWindow", "Trigger", nullptr));
        actionLine->setText(QApplication::translate("MainWindow", "Line", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLine->setShortcut(QApplication::translate("MainWindow", "4", nullptr));
#endif // QT_NO_SHORTCUT
        actionBar->setText(QApplication::translate("MainWindow", "Bar", nullptr));
#ifndef QT_NO_SHORTCUT
        actionBar->setShortcut(QApplication::translate("MainWindow", "5", nullptr));
#endif // QT_NO_SHORTCUT
        actionSpektrum->setText(QApplication::translate("MainWindow", "Spektrum", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSpektrum->setToolTip(QApplication::translate("MainWindow", "Poka\305\274 spektrum", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSpektrum->setShortcut(QApplication::translate("MainWindow", "6", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "Zapisz do pliku", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Zapis", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Otw\303\263rz", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionOtw_rz->setText(QApplication::translate("MainWindow", "Otw\303\263rz", nullptr));
        actionOtw_rz->setIconText(QApplication::translate("MainWindow", "Otw\303\263rz", nullptr));
        actionZapisz_domy_lne->setText(QApplication::translate("MainWindow", "Zapisz domy\305\233lne", nullptr));
        actionKatalog->setText(QApplication::translate("MainWindow", "Katalog", nullptr));
        menuUstwienia->setTitle(QApplication::translate("MainWindow", "Ustwienia", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Input", nullptr));
        selectInput2->setText(QApplication::translate("MainWindow", "2", nullptr));
        selectInput3->setText(QApplication::translate("MainWindow", "3", nullptr));
        selectInput1->setText(QApplication::translate("MainWindow", "1", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Window", nullptr));
        radioBtn_rect->setText(QApplication::translate("MainWindow", "Rectangle", nullptr));
        radioBtn_hann->setText(QApplication::translate("MainWindow", "Hann", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "PWM [%]", nullptr));
        pwmLabel2->setText(QApplication::translate("MainWindow", "0", nullptr));
        pwmLabel3->setText(QApplication::translate("MainWindow", "0", nullptr));
        pwmLabel1->setText(QApplication::translate("MainWindow", "0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_config), QApplication::translate("MainWindow", "Konfiguracja", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Zapisz do ", nullptr));
        radio_saveAllDir->setText(QApplication::translate("MainWindow", "Mieszane", nullptr));
        radio_handOpen->setText(QApplication::translate("MainWindow", "D\305\202o\305\204 rozlu\305\272niona", nullptr));
        radio_handClose->setText(QApplication::translate("MainWindow", "D\305\202o\305\204 zaci\305\233ni\304\231ta", nullptr));
        pushButto_kat->setText(QApplication::translate("MainWindow", "Otw\303\263rz katalog", nullptr));
        toolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_save), QApplication::translate("MainWindow", "Zapis ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
