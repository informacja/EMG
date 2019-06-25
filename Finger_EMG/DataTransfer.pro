#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T11:41:27
#
#-------------------------------------------------

QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = DataTransfer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    iir/iir/Biquad.cpp \
    iir/iir/Butterworth.cpp \
    iir/iir/Cascade.cpp \
    iir/iir/ChebyshevI.cpp \
    iir/iir/ChebyshevII.cpp \
    iir/iir/Custom.cpp \
    iir/iir/PoleFilter.cpp \
    iir/iir/RBJ.cpp \
    iir/iir/State.cpp \
    main.cpp \
    mainwindow.cpp \
    thread.cpp \
    chart.cpp \
    kissfft-131/kiss_fft.c \
    audio/wavfilereader.cpp \
    audio/wavefilewriter.cpp
#    kissfft-131/kiss_fft.c
#    spectrum/app/engine.cpp \
#    spectrum/app/frequencyspectrum.cpp \
#    spectrum/app/levelmeter.cpp \
#    spectrum/app/main.cpp \
#    spectrum/app/mainwidget.cpp \
#    spectrum/app/settingsdialog.cpp \
#    spectrum/app/spectrograph.cpp \
#    spectrum/app/spectrumanalyser.cpp \
#    spectrum/app/tonegenerator.cpp \
#    spectrum/app/tonegeneratordialog.cpp \
#    spectrum/app/utils.cpp \
#    spectrum/app/waveform.cpp \


HEADERS += \
    iir/iir/Biquad.h \
    iir/iir/Butterworth.h \
    iir/iir/Cascade.h \
    iir/iir/ChebyshevI.h \
    iir/iir/ChebyshevII.h \
    iir/iir/Common.h \
    iir/iir/Custom.h \
    iir/iir/Layout.h \
    iir/iir/MathSupplement.h \
    iir/iir/PoleFilter.h \
    iir/iir/RBJ.h \
    iir/iir/State.h \
    iir/iir/Types.h \
    mainwindow.h \
    release/moc_predefs.h \
    thread.h \
    chart.h \
    pre_headers.h \
    kissfft-131/kiss_fft.h \
    audio/wavfilereader.h \
    audio/wavefilewriter.h \
    ui_mainwindow.h
#    wavfile.h
#    spectrum/app/engine.h \
#    spectrum/app/frequencyspectrum.h \
#    spectrum/app/levelmeter.h \
#    spectrum/app/mainwidget.h \
#    spectrum/app/progressbar.h \
#    spectrum/app/settingsdialog.h \
#    spectrum/app/spectrograph.h \
#    spectrum/app/spectrum.h \
#    spectrum/app/spectrumanalyser.h \
#    spectrum/app/tonegenerator.h \
#    spectrum/app/tonegeneratordialog.h \
#    spectrum/app/utils.h \
#    spectrum/app/waveform.h \


FORMS += \
        mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#DISTFILES +=


# Added by Piotr

*msvc* { # visual studio spec filter
  QMAKE_CXXFLAGS += -MP8
}

CONFIG += precompile_header

#PRECOMPILED_HEADER = pre_headers.h


#SUBDIRS += \
#    spectrum/app/app.pro \
#    spectrum/spectrum.pro

LIBS += -L"iir/"
LIBS += -L"iir/iir"
LIBS += -L"kissfft-131"
