/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
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
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *selectInput1;
    QCheckBox *selectInput3;
    QCheckBox *selectInput2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *pwmLabel1;
    QLabel *pwmLabel2;
    QSlider *pwmValue1;
    QLabel *pwmLabel3;
    QSlider *pwmValue3;
    QSlider *pwmValue2;
    QSlider *verticalSlider;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(688, 406);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setAcceptDrops(true);
        MainWindow->setIconSize(QSize(24, 24));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionRun->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon);
        actionTrigger = new QAction(MainWindow);
        actionTrigger->setObjectName(QStringLiteral("actionTrigger"));
        actionTrigger->setCheckable(true);
        actionTrigger->setChecked(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/trigger.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTrigger->setIcon(icon1);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        actionLine->setCheckable(true);
        actionLine->setChecked(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/lines.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine->setIcon(icon2);
        actionLine->setIconVisibleInMenu(true);
        actionBar = new QAction(MainWindow);
        actionBar->setObjectName(QStringLiteral("actionBar"));
        actionBar->setCheckable(true);
        actionBar->setChecked(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/bars.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBar->setIcon(icon3);
        actionSpektrum = new QAction(MainWindow);
        actionSpektrum->setObjectName(QStringLiteral("actionSpektrum"));
        actionSpektrum->setCheckable(true);
        actionSpektrum->setChecked(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/heartbeat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSpektrum->setIcon(icon4);
        actionSpektrum->setIconVisibleInMenu(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setCheckable(true);
        actionSave->setChecked(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon5);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOtw_rz = new QAction(MainWindow);
        actionOtw_rz->setObjectName(QStringLiteral("actionOtw_rz"));
#ifndef QT_NO_TOOLTIP
        actionOtw_rz->setToolTip(QString::fromUtf8("Otw\303\263rz"));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionOtw_rz->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionOtw_rz->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS
        actionOtw_rz->setAutoRepeat(false);
        actionZapisz_domy_lne = new QAction(MainWindow);
        actionZapisz_domy_lne->setObjectName(QStringLiteral("actionZapisz_domy_lne"));
        actionKatalog = new QAction(MainWindow);
        actionKatalog->setObjectName(QStringLiteral("actionKatalog"));
        actionKatalog->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 688, 20));
#ifndef QT_NO_TOOLTIP
        menuBar->setToolTip(QStringLiteral("sdf"));
#endif // QT_NO_TOOLTIP
        menuBar->setToolTipDuration(44);
#ifndef QT_NO_STATUSTIP
        menuBar->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        menuUstwienia = new QMenu(menuBar);
        menuUstwienia->setObjectName(QStringLiteral("menuUstwienia"));
        menuUstwienia->setMouseTracking(false);
        menuUstwienia->setAcceptDrops(false);
#ifndef QT_NO_TOOLTIP
        menuUstwienia->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        menuUstwienia->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setAcceptDrops(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAutoFillBackground(true);
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(171, 300));
        dockWidget->setMaximumSize(QSize(171, 524287));
        dockWidget->setStyleSheet(QLatin1String("background-color: rgb(64, 64, 64);\n"
"color: rgb(255, 255, 255);"));
        dockWidget->setFloating(false);
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        selectInput1 = new QCheckBox(groupBox);
        selectInput1->setObjectName(QStringLiteral("selectInput1"));
        selectInput1->setChecked(true);
        selectInput1->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput1, 0, 0, 1, 1);

        selectInput3 = new QCheckBox(groupBox);
        selectInput3->setObjectName(QStringLiteral("selectInput3"));
        selectInput3->setChecked(true);
        selectInput3->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput3, 0, 2, 1, 1);

        selectInput2 = new QCheckBox(groupBox);
        selectInput2->setObjectName(QStringLiteral("selectInput2"));
        selectInput2->setChecked(false);
        selectInput2->setAutoExclusive(false);

        gridLayout_2->addWidget(selectInput2, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pwmLabel1 = new QLabel(groupBox_2);
        pwmLabel1->setObjectName(QStringLiteral("pwmLabel1"));
        pwmLabel1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel1, 0, 0, 1, 1);

        pwmLabel2 = new QLabel(groupBox_2);
        pwmLabel2->setObjectName(QStringLiteral("pwmLabel2"));
        pwmLabel2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel2, 0, 1, 1, 1);

        pwmValue1 = new QSlider(groupBox_2);
        pwmValue1->setObjectName(QStringLiteral("pwmValue1"));
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
        pwmLabel3->setObjectName(QStringLiteral("pwmLabel3"));
        pwmLabel3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pwmLabel3, 0, 2, 1, 1);

        pwmValue3 = new QSlider(groupBox_2);
        pwmValue3->setObjectName(QStringLiteral("pwmValue3"));
        pwmValue3->setMaximum(100);
        pwmValue3->setOrientation(Qt::Vertical);
        pwmValue3->setTickPosition(QSlider::TicksBothSides);

        gridLayout->addWidget(pwmValue3, 1, 2, 1, 1);

        pwmValue2 = new QSlider(groupBox_2);
        pwmValue2->setObjectName(QStringLiteral("pwmValue2"));
        pwmValue2->setMaximum(100);
        pwmValue2->setOrientation(Qt::Vertical);
        pwmValue2->setTickPosition(QSlider::TicksBothSides);

        gridLayout->addWidget(pwmValue2, 1, 1, 1, 1);

        verticalSlider = new QSlider(groupBox_2);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 1, 3, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 0, 1, 1);

        textEdit = new QTextEdit(dockWidgetContents);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setMaximumSize(QSize(16777215, 20));
        textEdit->setBaseSize(QSize(0, 10));
        textEdit->setAutoFillBackground(true);
        textEdit->setInputMethodHints(Qt::ImhNone);
        textEdit->setTabChangesFocus(false);
        textEdit->setLineWrapMode(QTextEdit::WidgetWidth);

        gridLayout_3->addWidget(textEdit, 1, 0, 1, 1);

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

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PWM Controller", 0));
        actionRun->setText(QApplication::translate("MainWindow", "Run", 0));
        actionRun->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        actionTrigger->setText(QApplication::translate("MainWindow", "Trigger", 0));
        actionLine->setText(QApplication::translate("MainWindow", "Line", 0));
        actionLine->setShortcut(QApplication::translate("MainWindow", "4", 0));
        actionBar->setText(QApplication::translate("MainWindow", "Bar", 0));
        actionBar->setShortcut(QApplication::translate("MainWindow", "5", 0));
        actionSpektrum->setText(QApplication::translate("MainWindow", "Spektrum", 0));
#ifndef QT_NO_TOOLTIP
        actionSpektrum->setToolTip(QApplication::translate("MainWindow", "Poka\305\274 spektrum", 0));
#endif // QT_NO_TOOLTIP
        actionSpektrum->setShortcut(QApplication::translate("MainWindow", "6", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Zapisz do pliku", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Zapis", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Otw\303\263rz", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionOtw_rz->setText(QApplication::translate("MainWindow", "Otw\303\263rz", 0));
        actionOtw_rz->setIconText(QApplication::translate("MainWindow", "Otw\303\263rz", 0));
        actionZapisz_domy_lne->setText(QApplication::translate("MainWindow", "Zapisz domy\305\233lne", 0));
        actionKatalog->setText(QApplication::translate("MainWindow", "Katalog", 0));
        menuUstwienia->setTitle(QApplication::translate("MainWindow", "Ustwienia", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Input", 0));
        selectInput1->setText(QApplication::translate("MainWindow", "1", 0));
        selectInput3->setText(QApplication::translate("MainWindow", "3", 0));
        selectInput2->setText(QApplication::translate("MainWindow", "2", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "PWM [%]", 0));
        pwmLabel1->setText(QApplication::translate("MainWindow", "0", 0));
        pwmLabel2->setText(QApplication::translate("MainWindow", "0", 0));
        pwmLabel3->setText(QApplication::translate("MainWindow", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
