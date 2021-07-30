#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //HiDPI pixmaps
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication a(argc, argv);
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    MainWindow w;
    w.show();

    return a.exec();
}
