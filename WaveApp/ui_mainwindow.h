/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
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
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_4;
    QLabel *path;
    QCommandLinkButton *commandLinkButton_show;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_path;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_return;
    QPushButton *pushButton_enter;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkBoxClipboard;
    QFrame *line;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *selectInput2;
    QCheckBox *selectInput3;
    QCheckBox *selectInput1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelSavingTime;
    QSpinBox *spinBox;
    QFrame *line_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(688, 582);
        MainWindow->setMinimumSize(QSize(400, 300));
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
        actionLine->setChecked(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/lines.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine->setIcon(icon2);
        actionBar = new QAction(MainWindow);
        actionBar->setObjectName(QString::fromUtf8("actionBar"));
        actionBar->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/bars.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBar->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 688, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setMinimumSize(QSize(171, 327));
        dockWidget->setMaximumSize(QSize(171, 524287));
        dockWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 64, 64);\n"
"color: rgb(255, 255, 255);"));
        dockWidget->setFloating(false);
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        progressBar = new QProgressBar(dockWidgetContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout_3->addWidget(progressBar, 25, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_4->setContentsMargins(-1, 0, 0, -1);
        path = new QLabel(dockWidgetContents);
        path->setObjectName(QString::fromUtf8("path"));

        horizontalLayout_4->addWidget(path);

        commandLinkButton_show = new QCommandLinkButton(dockWidgetContents);
        commandLinkButton_show->setObjectName(QString::fromUtf8("commandLinkButton_show"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(commandLinkButton_show->sizePolicy().hasHeightForWidth());
        commandLinkButton_show->setSizePolicy(sizePolicy);
        commandLinkButton_show->setIconSize(QSize(20, 20));
        commandLinkButton_show->setAutoDefault(false);
        commandLinkButton_show->setDefault(false);

        horizontalLayout_4->addWidget(commandLinkButton_show);


        gridLayout_3->addLayout(horizontalLayout_4, 13, 0, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_path = new QLineEdit(dockWidgetContents);
        lineEdit_path->setObjectName(QString::fromUtf8("lineEdit_path"));

        horizontalLayout_2->addWidget(lineEdit_path);


        gridLayout_3->addLayout(horizontalLayout_2, 22, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_return = new QPushButton(dockWidgetContents);
        pushButton_return->setObjectName(QString::fromUtf8("pushButton_return"));

        horizontalLayout->addWidget(pushButton_return);

        pushButton_enter = new QPushButton(dockWidgetContents);
        pushButton_enter->setObjectName(QString::fromUtf8("pushButton_enter"));

        horizontalLayout->addWidget(pushButton_enter);


        gridLayout_3->addLayout(horizontalLayout, 30, 0, 3, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 33, 0, 1, 1);

        checkBoxClipboard = new QCheckBox(dockWidgetContents);
        checkBoxClipboard->setObjectName(QString::fromUtf8("checkBoxClipboard"));
        checkBoxClipboard->setEnabled(true);

        gridLayout_3->addWidget(checkBoxClipboard, 23, 0, 1, 1);

        line = new QFrame(dockWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 24, 0, 1, 1);

        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        selectInput2 = new QCheckBox(groupBox);
        selectInput2->setObjectName(QString::fromUtf8("selectInput2"));
        selectInput2->setChecked(true);
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


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelSavingTime = new QLabel(dockWidgetContents);
        labelSavingTime->setObjectName(QString::fromUtf8("labelSavingTime"));
        labelSavingTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(labelSavingTime);

        spinBox = new QSpinBox(dockWidgetContents);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(3600);
        spinBox->setStepType(QAbstractSpinBox::DefaultStepType);
        spinBox->setValue(10);

        horizontalLayout_3->addWidget(spinBox);


        gridLayout_3->addLayout(horizontalLayout_3, 26, 0, 1, 1);

        line_2 = new QFrame(dockWidgetContents);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 27, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionTrigger);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLine);
        mainToolBar->addAction(actionBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PWM Controller", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
#if QT_CONFIG(shortcut)
        actionRun->setShortcut(QCoreApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTrigger->setText(QCoreApplication::translate("MainWindow", "Trigger", nullptr));
        actionLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
#if QT_CONFIG(shortcut)
        actionLine->setShortcut(QCoreApplication::translate("MainWindow", "1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBar->setText(QCoreApplication::translate("MainWindow", "Bar", nullptr));
#if QT_CONFIG(shortcut)
        actionBar->setShortcut(QCoreApplication::translate("MainWindow", "2", nullptr));
#endif // QT_CONFIG(shortcut)
        path->setText(QCoreApplication::translate("MainWindow", "Output file path", nullptr));
        commandLinkButton_show->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
#if QT_CONFIG(shortcut)
        commandLinkButton_show->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        lineEdit_path->setText(QCoreApplication::translate("MainWindow", "../matlab/out.wav", nullptr));
        pushButton_return->setText(QCoreApplication::translate("MainWindow", "Return", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_return->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_enter->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_enter->setShortcut(QCoreApplication::translate("MainWindow", "Enter", nullptr));
#endif // QT_CONFIG(shortcut)
        checkBoxClipboard->setText(QCoreApplication::translate("MainWindow", "Copy filepath to clipboard", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Input", nullptr));
        selectInput2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        selectInput3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        selectInput1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelSavingTime->setText(QCoreApplication::translate("MainWindow", "Recording time:", nullptr));
        spinBox->setSuffix(QCoreApplication::translate("MainWindow", " s", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
