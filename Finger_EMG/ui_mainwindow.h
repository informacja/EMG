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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_config;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *selectInput1;
    QCheckBox *selectInput2;
    QCheckBox *selectInput3;
    QGroupBox *groupBox_window;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioBtn_rect;
    QRadioButton *radioBtn_hann;
    QRadioButton *radioBtn_hamm;
    QGroupBox *groupBox_bw_filtr;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBox_bandStop;
    QSpinBox *spinBox_BandStop;
    QSpinBox *spinBox_BandStop_width;
    QCheckBox *checkBox_highPass;
    QSpinBox *spinBox_HiPass;
    QCheckBox *checkBox_fill1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *pwmLabel1;
    QSlider *pwmValue2;
    QSlider *pwmValue3;
    QLabel *pwmLabel2;
    QLabel *pwmLabel3;
    QSlider *pwmValue1;
    QWidget *tab_save;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radio_saveAllDir;
    QRadioButton *radio_handOpen;
    QRadioButton *radio_handClose;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QLineEdit *lineEdit_path;
    QLabel *label_2;
    QLineEdit *lineEdit_fileN;
    QPushButton *pushButto_kat;
    QPushButton *pushButton_openFile;
    QSpacerItem *verticalSpacer_5;
    QFrame *line_2;
    QProgressBar *progressBar;
    QFormLayout *formLayout;
    QLabel *label_Nsample;
    QSpinBox *spinBox_nDataPerFile;
    QFrame *line_5;
    QLabel *label_3;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton_return;
    QToolButton *toolButton_enter;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(797, 485);
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
        menuBar->setGeometry(QRect(0, 0, 797, 20));
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
        statusBar->setStyleSheet(QString::fromUtf8("font: 75 8pt \"MS Shell Dlg 2\";"));
        statusBar->setInputMethodHints(Qt::ImhNone);
        statusBar->setSizeGripEnabled(false);
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
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 150));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab_config = new QWidget();
        tab_config->setObjectName(QString::fromUtf8("tab_config"));
        verticalLayout_2 = new QVBoxLayout(tab_config);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab_config);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        selectInput1 = new QCheckBox(groupBox);
        selectInput1->setObjectName(QString::fromUtf8("selectInput1"));
        selectInput1->setChecked(true);
        selectInput1->setAutoExclusive(false);

        horizontalLayout_2->addWidget(selectInput1);

        selectInput2 = new QCheckBox(groupBox);
        selectInput2->setObjectName(QString::fromUtf8("selectInput2"));
        selectInput2->setChecked(false);
        selectInput2->setAutoExclusive(false);

        horizontalLayout_2->addWidget(selectInput2);

        selectInput3 = new QCheckBox(groupBox);
        selectInput3->setObjectName(QString::fromUtf8("selectInput3"));
        selectInput3->setChecked(false);
        selectInput3->setAutoExclusive(false);

        horizontalLayout_2->addWidget(selectInput3);


        verticalLayout_2->addWidget(groupBox);

        groupBox_window = new QGroupBox(tab_config);
        groupBox_window->setObjectName(QString::fromUtf8("groupBox_window"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(groupBox_window->sizePolicy().hasHeightForWidth());
        groupBox_window->setSizePolicy(sizePolicy1);
        groupBox_window->setMinimumSize(QSize(0, 40));
        verticalLayout_3 = new QVBoxLayout(groupBox_window);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        radioBtn_rect = new QRadioButton(groupBox_window);
        radioBtn_rect->setObjectName(QString::fromUtf8("radioBtn_rect"));
        radioBtn_rect->setChecked(false);

        verticalLayout_3->addWidget(radioBtn_rect);

        radioBtn_hann = new QRadioButton(groupBox_window);
        radioBtn_hann->setObjectName(QString::fromUtf8("radioBtn_hann"));
        radioBtn_hann->setChecked(true);
        radioBtn_hann->setAutoRepeat(false);

        verticalLayout_3->addWidget(radioBtn_hann);

        radioBtn_hamm = new QRadioButton(groupBox_window);
        radioBtn_hamm->setObjectName(QString::fromUtf8("radioBtn_hamm"));

        verticalLayout_3->addWidget(radioBtn_hamm);


        verticalLayout_2->addWidget(groupBox_window);

        groupBox_bw_filtr = new QGroupBox(tab_config);
        groupBox_bw_filtr->setObjectName(QString::fromUtf8("groupBox_bw_filtr"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_bw_filtr->sizePolicy().hasHeightForWidth());
        groupBox_bw_filtr->setSizePolicy(sizePolicy2);
        verticalLayout_6 = new QVBoxLayout(groupBox_bw_filtr);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        checkBox_bandStop = new QCheckBox(groupBox_bw_filtr);
        checkBox_bandStop->setObjectName(QString::fromUtf8("checkBox_bandStop"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox_bandStop->sizePolicy().hasHeightForWidth());
        checkBox_bandStop->setSizePolicy(sizePolicy3);
        checkBox_bandStop->setChecked(true);

        verticalLayout_6->addWidget(checkBox_bandStop);

        spinBox_BandStop = new QSpinBox(groupBox_bw_filtr);
        spinBox_BandStop->setObjectName(QString::fromUtf8("spinBox_BandStop"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinBox_BandStop->sizePolicy().hasHeightForWidth());
        spinBox_BandStop->setSizePolicy(sizePolicy4);
        spinBox_BandStop->setMaximumSize(QSize(16777215, 16777215));
        spinBox_BandStop->setSizeIncrement(QSize(22, 22));
        spinBox_BandStop->setBaseSize(QSize(22, 11));
        spinBox_BandStop->setLayoutDirection(Qt::LeftToRight);
        spinBox_BandStop->setAutoFillBackground(false);
        spinBox_BandStop->setInputMethodHints(Qt::ImhDigitsOnly);
        spinBox_BandStop->setWrapping(true);
        spinBox_BandStop->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_BandStop->setAccelerated(true);
        spinBox_BandStop->setMinimum(1);
        spinBox_BandStop->setMaximum(1024);
        spinBox_BandStop->setSingleStep(1);
        spinBox_BandStop->setStepType(QAbstractSpinBox::DefaultStepType);
        spinBox_BandStop->setValue(50);

        verticalLayout_6->addWidget(spinBox_BandStop, 0, Qt::AlignHCenter);

        spinBox_BandStop_width = new QSpinBox(groupBox_bw_filtr);
        spinBox_BandStop_width->setObjectName(QString::fromUtf8("spinBox_BandStop_width"));
        sizePolicy4.setHeightForWidth(spinBox_BandStop_width->sizePolicy().hasHeightForWidth());
        spinBox_BandStop_width->setSizePolicy(sizePolicy4);
        spinBox_BandStop_width->setToolTipDuration(-8);
        spinBox_BandStop_width->setMinimum(1);
        spinBox_BandStop_width->setValue(3);

        verticalLayout_6->addWidget(spinBox_BandStop_width, 0, Qt::AlignHCenter);

        checkBox_highPass = new QCheckBox(groupBox_bw_filtr);
        checkBox_highPass->setObjectName(QString::fromUtf8("checkBox_highPass"));
        checkBox_highPass->setChecked(true);

        verticalLayout_6->addWidget(checkBox_highPass);

        spinBox_HiPass = new QSpinBox(groupBox_bw_filtr);
        spinBox_HiPass->setObjectName(QString::fromUtf8("spinBox_HiPass"));
        sizePolicy4.setHeightForWidth(spinBox_HiPass->sizePolicy().hasHeightForWidth());
        spinBox_HiPass->setSizePolicy(sizePolicy4);
        spinBox_HiPass->setToolTipDuration(3);
        spinBox_HiPass->setMinimum(1);
        spinBox_HiPass->setMaximum(512);
        spinBox_HiPass->setValue(15);

        verticalLayout_6->addWidget(spinBox_HiPass, 0, Qt::AlignHCenter);

        checkBox_fill1 = new QCheckBox(groupBox_bw_filtr);
        checkBox_fill1->setObjectName(QString::fromUtf8("checkBox_fill1"));
        checkBox_fill1->setAutoExclusive(false);

        verticalLayout_6->addWidget(checkBox_fill1, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout_2->addWidget(groupBox_bw_filtr, 0, Qt::AlignHCenter);

        groupBox_2 = new QGroupBox(tab_config);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy5);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pwmLabel1 = new QLabel(groupBox_2);
        pwmLabel1->setObjectName(QString::fromUtf8("pwmLabel1"));
        pwmLabel1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel1, 0, 0, 1, 1);

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

        pwmLabel2 = new QLabel(groupBox_2);
        pwmLabel2->setObjectName(QString::fromUtf8("pwmLabel2"));
        pwmLabel2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel2, 0, 1, 1, 1);

        pwmLabel3 = new QLabel(groupBox_2);
        pwmLabel3->setObjectName(QString::fromUtf8("pwmLabel3"));
        pwmLabel3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel3, 0, 2, 1, 1);

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


        verticalLayout_2->addWidget(groupBox_2);

        tabWidget->addTab(tab_config, QString());
        tab_save = new QWidget();
        tab_save->setObjectName(QString::fromUtf8("tab_save"));
        verticalLayout = new QVBoxLayout(tab_save);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(tab_save);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy6);
        groupBox_4->setMinimumSize(QSize(0, 90));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        radio_saveAllDir = new QRadioButton(groupBox_4);
        radio_saveAllDir->setObjectName(QString::fromUtf8("radio_saveAllDir"));

        verticalLayout_5->addWidget(radio_saveAllDir);

        radio_handOpen = new QRadioButton(groupBox_4);
        radio_handOpen->setObjectName(QString::fromUtf8("radio_handOpen"));

        verticalLayout_5->addWidget(radio_handOpen);

        radio_handClose = new QRadioButton(groupBox_4);
        radio_handClose->setObjectName(QString::fromUtf8("radio_handClose"));

        verticalLayout_5->addWidget(radio_handClose);

        radioButton = new QRadioButton(groupBox_4);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_5->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_4);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_5->addWidget(radioButton_2);


        verticalLayout->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(tab_save);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit_path = new QLineEdit(tab_save);
        lineEdit_path->setObjectName(QString::fromUtf8("lineEdit_path"));
        lineEdit_path->setInputMethodHints(Qt::ImhNone);

        verticalLayout->addWidget(lineEdit_path);

        label_2 = new QLabel(tab_save);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit_fileN = new QLineEdit(tab_save);
        lineEdit_fileN->setObjectName(QString::fromUtf8("lineEdit_fileN"));
        lineEdit_fileN->setAutoFillBackground(false);

        verticalLayout->addWidget(lineEdit_fileN);

        pushButto_kat = new QPushButton(tab_save);
        pushButto_kat->setObjectName(QString::fromUtf8("pushButto_kat"));
        sizePolicy3.setHeightForWidth(pushButto_kat->sizePolicy().hasHeightForWidth());
        pushButto_kat->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(pushButto_kat);

        pushButton_openFile = new QPushButton(tab_save);
        pushButton_openFile->setObjectName(QString::fromUtf8("pushButton_openFile"));
        QSizePolicy sizePolicy7(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(pushButton_openFile->sizePolicy().hasHeightForWidth());
        pushButton_openFile->setSizePolicy(sizePolicy7);

        verticalLayout->addWidget(pushButton_openFile);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        line_2 = new QFrame(tab_save);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        progressBar = new QProgressBar(tab_save);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(1);

        verticalLayout->addWidget(progressBar);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setVerticalSpacing(35);
        formLayout->setContentsMargins(-1, 0, 0, -1);
        label_Nsample = new QLabel(tab_save);
        label_Nsample->setObjectName(QString::fromUtf8("label_Nsample"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_Nsample);

        spinBox_nDataPerFile = new QSpinBox(tab_save);
        spinBox_nDataPerFile->setObjectName(QString::fromUtf8("spinBox_nDataPerFile"));
        sizePolicy4.setHeightForWidth(spinBox_nDataPerFile->sizePolicy().hasHeightForWidth());
        spinBox_nDataPerFile->setSizePolicy(sizePolicy4);
        spinBox_nDataPerFile->setMinimum(1);
        spinBox_nDataPerFile->setMaximum(1000);
        spinBox_nDataPerFile->setValue(6);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox_nDataPerFile);


        verticalLayout->addLayout(formLayout);

        line_5 = new QFrame(tab_save);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        label_3 = new QLabel(tab_save);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3, 0, Qt::AlignHCenter);

        line = new QFrame(tab_save);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setContentsMargins(-1, 0, -1, 0);
        toolButton_return = new QToolButton(tab_save);
        toolButton_return->setObjectName(QString::fromUtf8("toolButton_return"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(toolButton_return->sizePolicy().hasHeightForWidth());
        toolButton_return->setSizePolicy(sizePolicy8);
        toolButton_return->setIconSize(QSize(32, 32));
        toolButton_return->setPopupMode(QToolButton::DelayedPopup);
        toolButton_return->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        toolButton_return->setAutoRaise(false);

        gridLayout_2->addWidget(toolButton_return, 0, 0, 1, 1);

        toolButton_enter = new QToolButton(tab_save);
        toolButton_enter->setObjectName(QString::fromUtf8("toolButton_enter"));
        sizePolicy8.setHeightForWidth(toolButton_enter->sizePolicy().hasHeightForWidth());
        toolButton_enter->setSizePolicy(sizePolicy8);
        toolButton_enter->setCursor(QCursor(Qt::PointingHandCursor));
        toolButton_enter->setAutoFillBackground(false);
        toolButton_enter->setIconSize(QSize(32, 32));
        toolButton_enter->setCheckable(false);
        toolButton_enter->setChecked(false);
        toolButton_enter->setAutoRepeat(false);
        toolButton_enter->setAutoExclusive(false);
        toolButton_enter->setPopupMode(QToolButton::DelayedPopup);
        toolButton_enter->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton_enter->setAutoRaise(false);
        toolButton_enter->setArrowType(Qt::NoArrow);

        gridLayout_2->addWidget(toolButton_enter, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tab_save, QString());

        verticalLayout_4->addWidget(tabWidget);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
#ifndef QT_NO_SHORTCUT
        pwmLabel2->setBuddy(pwmLabel2);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(selectInput1, selectInput2);
        QWidget::setTabOrder(selectInput2, selectInput3);
        QWidget::setTabOrder(selectInput3, radioBtn_rect);
        QWidget::setTabOrder(radioBtn_rect, radioBtn_hann);
        QWidget::setTabOrder(radioBtn_hann, checkBox_bandStop);
        QWidget::setTabOrder(checkBox_bandStop, spinBox_BandStop);
        QWidget::setTabOrder(spinBox_BandStop, pwmValue1);
        QWidget::setTabOrder(pwmValue1, pwmValue2);
        QWidget::setTabOrder(pwmValue2, pwmValue3);
        QWidget::setTabOrder(pwmValue3, radio_saveAllDir);
        QWidget::setTabOrder(radio_saveAllDir, radio_handOpen);
        QWidget::setTabOrder(radio_handOpen, radio_handClose);
        QWidget::setTabOrder(radio_handClose, checkBox_highPass);
        QWidget::setTabOrder(checkBox_highPass, spinBox_HiPass);

        menuBar->addAction(menuUstwienia->menuAction());
        menuUstwienia->addAction(actionOtw_rz);
        menuUstwienia->addAction(actionZapisz_domy_lne);
        menuUstwienia->addAction(actionKatalog);
        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionTrigger);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLine);
        mainToolBar->addAction(actionSpektrum);
        mainToolBar->addAction(actionBar);
        mainToolBar->addSeparator();
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Finger EMG", nullptr));
        actionRun->setText(QApplication::translate("MainWindow", "Run", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_NO_SHORTCUT
        actionTrigger->setText(QApplication::translate("MainWindow", "Trigger", nullptr));
        actionLine->setText(QApplication::translate("MainWindow", "Line", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLine->setShortcut(QApplication::translate("MainWindow", "1", nullptr));
#endif // QT_NO_SHORTCUT
        actionBar->setText(QApplication::translate("MainWindow", "Bar", nullptr));
#ifndef QT_NO_SHORTCUT
        actionBar->setShortcut(QApplication::translate("MainWindow", "3", nullptr));
#endif // QT_NO_SHORTCUT
        actionSpektrum->setText(QApplication::translate("MainWindow", "Spektrum", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSpektrum->setToolTip(QApplication::translate("MainWindow", "Poka\305\274 spektrum", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSpektrum->setShortcut(QApplication::translate("MainWindow", "2", nullptr));
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
        selectInput1->setText(QApplication::translate("MainWindow", "1", nullptr));
#ifndef QT_NO_SHORTCUT
        selectInput1->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_NO_SHORTCUT
        selectInput2->setText(QApplication::translate("MainWindow", "2", nullptr));
#ifndef QT_NO_SHORTCUT
        selectInput2->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_NO_SHORTCUT
        selectInput3->setText(QApplication::translate("MainWindow", "3", nullptr));
#ifndef QT_NO_SHORTCUT
        selectInput3->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_window->setTitle(QApplication::translate("MainWindow", "Window", nullptr));
        radioBtn_rect->setText(QApplication::translate("MainWindow", "Rectangle", nullptr));
#ifndef QT_NO_SHORTCUT
        radioBtn_rect->setShortcut(QApplication::translate("MainWindow", "Ctrl+4", nullptr));
#endif // QT_NO_SHORTCUT
        radioBtn_hann->setText(QApplication::translate("MainWindow", "Hann", nullptr));
#ifndef QT_NO_SHORTCUT
        radioBtn_hann->setShortcut(QApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_NO_SHORTCUT
        radioBtn_hamm->setText(QApplication::translate("MainWindow", "Hamming", nullptr));
#ifndef QT_NO_SHORTCUT
        radioBtn_hamm->setShortcut(QApplication::translate("MainWindow", "Ctrl+6", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_bw_filtr->setTitle(QApplication::translate("MainWindow", "Butterworth filtr", nullptr));
        checkBox_bandStop->setText(QApplication::translate("MainWindow", "Band Stop", nullptr));
#ifndef QT_NO_SHORTCUT
        checkBox_bandStop->setShortcut(QApplication::translate("MainWindow", "Ctrl+7", nullptr));
#endif // QT_NO_SHORTCUT
        spinBox_BandStop->setSpecialValueText(QApplication::translate("MainWindow", "drfg", nullptr));
        spinBox_BandStop->setSuffix(QApplication::translate("MainWindow", " Hz", nullptr));
        spinBox_BandStop->setPrefix(QString());
        spinBox_BandStop_width->setSuffix(QApplication::translate("MainWindow", " width", nullptr));
        checkBox_highPass->setText(QApplication::translate("MainWindow", "High Pass", nullptr));
#ifndef QT_NO_SHORTCUT
        checkBox_highPass->setShortcut(QApplication::translate("MainWindow", "Ctrl+8", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        spinBox_HiPass->setToolTip(QApplication::translate("MainWindow", "t2", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinBox_HiPass->setStatusTip(QApplication::translate("MainWindow", "64", nullptr));
#endif // QT_NO_STATUSTIP
        spinBox_HiPass->setSuffix(QApplication::translate("MainWindow", " Hz", nullptr));
        checkBox_fill1->setText(QApplication::translate("MainWindow", "Fill data to 1 (test)", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "PWM [%]", nullptr));
        pwmLabel1->setText(QApplication::translate("MainWindow", "0", nullptr));
        pwmLabel2->setText(QApplication::translate("MainWindow", "0", nullptr));
        pwmLabel3->setText(QApplication::translate("MainWindow", "0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_config), QApplication::translate("MainWindow", "Konfiguracja", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Zapisz do ", nullptr));
        radio_saveAllDir->setText(QApplication::translate("MainWindow", "Mieszane", nullptr));
#ifndef QT_NO_SHORTCUT
        radio_saveAllDir->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        radio_handOpen->setText(QApplication::translate("MainWindow", "D\305\202o\305\204 rozlu\305\272niona", nullptr));
#ifndef QT_NO_SHORTCUT
        radio_handOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_NO_SHORTCUT
        radio_handClose->setText(QApplication::translate("MainWindow", "D\305\202o\305\204 zaci\305\233ni\304\231ta", nullptr));
#ifndef QT_NO_SHORTCUT
        radio_handClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_NO_SHORTCUT
        radioButton->setText(QApplication::translate("MainWindow", "Palec wskazuj\304\205cy", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+4", nullptr));
#endif // QT_NO_SHORTCUT
        radioButton_2->setText(QApplication::translate("MainWindow", "Kciuk", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "Katalog", nullptr));
        lineEdit_path->setText(QApplication::translate("MainWindow", "../sample", nullptr));
        lineEdit_path->setPlaceholderText(QApplication::translate("MainWindow", "\305\232cie\305\274ka katalogu", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Nazwa pliku", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_fileN->setToolTip(QApplication::translate("MainWindow", "43", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lineEdit_fileN->setStatusTip(QApplication::translate("MainWindow", "23", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_fileN->setWhatsThis(QApplication::translate("MainWindow", "21", nullptr));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        lineEdit_fileN->setAccessibleName(QApplication::translate("MainWindow", "22", nullptr));
#endif // QT_NO_ACCESSIBILITY
        lineEdit_fileN->setPlaceholderText(QApplication::translate("MainWindow", "Nazwa pliku", nullptr));
        pushButto_kat->setText(QApplication::translate("MainWindow", "Otw\303\263rz katalog", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButto_kat->setShortcut(QApplication::translate("MainWindow", "Ctrl+0", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_openFile->setText(QApplication::translate("MainWindow", "Zamknij i poka\305\274 plik", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton_openFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_NO_SHORTCUT
        label_Nsample->setText(QApplication::translate("MainWindow", "N data per file", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Nagraj pr\303\263bk\304\231, naciskaj\304\205c", nullptr));
        toolButton_return->setText(QApplication::translate("MainWindow", "Return", nullptr));
#ifndef QT_NO_SHORTCUT
        toolButton_return->setShortcut(QApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_NO_SHORTCUT
        toolButton_enter->setText(QApplication::translate("MainWindow", "Enter", nullptr));
#ifndef QT_NO_SHORTCUT
        toolButton_enter->setShortcut(QApplication::translate("MainWindow", "Enter", nullptr));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab_save), QApplication::translate("MainWindow", "Zapis ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
