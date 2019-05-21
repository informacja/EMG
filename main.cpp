#include "mainwindow.h"/*
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    QImage myImage;
//    myImage.load("C:\\Users\\Puler\\Desktop\\ToDo.png");

//    QLabel myLabel;
//    myLabel.setPixmap(QPixmap::fromImage(myImage));

//    myLabel.show();

    // from resource
//        QGraphicsScene scene;
//       QGraphicsView view(&scene);
//       QPixmap qp = QPixmap(":/icons/zi.jpg");
//       if(qp.isNull())
//       {
//           printf("Yes its null\n");
//       }
//       else
//       {
//           printf("HAHA");
//           QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/icons/zi.jpg"));
//           scene.addItem(item);
//       }
//       view.show();


    w.show();
    //    w.showFullScreen();
//    QShortcut shortcut = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),
//                             parent);

//    a.setStyle("Fusion");
//    a.screens().
//     QRect rec = a.desktop()->screenGeometry();
//     int height = rec.height();
//     int width = rec.width();
    /* if(width < 1300)
       width = width - 100;
     else
       width = 1250;
     if(height < 900)
       height = height - 100;
     else
       height = 830;

     Window main;
     main.show();
     main.setMinimumSize(width, height);*/

    return a.exec();
}
