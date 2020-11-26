#include "chart.h"

Chart::Chart()
{
    for(int i=0; i<LOGMAX; i++)
        logTable[i]=(i/9)+log10((i%9)+1);
}

void Chart::drawLogGrid(QPainter &painter, QRect geometry)
{
    gx=geometry.x()+MX;
    gy=geometry.y()+MY;
    gw=geometry.width()-(2*MX);
    gh=geometry.height()-(2*MY);

    dx=gw/static_cast<double>(logTable[gridNumX]);
    dy=gh/static_cast<double>(gridNumY);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(backgroundColor);
    painter.setPen(pen);
    painter.setBrush(backgroundColor);
    painter.drawRect(geometry);

    // -----  frame ------------
    pen.setStyle(Qt::SolidLine);
    pen.setColor(gridColor);
    pen.setWidth(2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(gx, gy, gw, gh);
    // ----- grid ------------
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int px=1; px<gridNumX; px++)
        painter.drawLine(QLineF(gx+(logTable[px]*dx), gy, gx+(logTable[px]*dx), gy+gh));
    for(int py=1; py<gridNumY; py++)
        painter.drawLine(QLineF(gx, gy+(py*dy), gx+gw, gy+(py*dy)));
    // ------ desc ----------
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    pen.setColor(textColor);
    painter.setPen(pen);
    //dvx=maxValueX-minValueX;
    dvy=maxValueY-minValueY;
    int f=minValueX;
    for(int px=0; px<gridNumX; px++){

        if((px % 9) == 0){

            painter.drawText(QPointF(gx+logTable[px]*dx-(font.pointSize()), gy+gh+(font.pointSize()*2)), QString().sprintf("%4d",f));
            f*=10;
        }
    }
    painter.drawText(QPointF(gx+logTable[gridNumX]*dx-(font.pointSize()), gy+gh+(font.pointSize()*2)), QString().sprintf("%4d",maxValueX));


    for(int py=0; py<=gridNumY; py++)
        painter.drawText(QPointF(gx-(font.pointSize()*4), gy+(font.pointSize()/2)+py*dy), QString().sprintf("%4d", static_cast<int>(maxValueY-(dvy*py)/gridNumY)));
}

void Chart::drawLogData(QPainter &painter, QVector<double> &data)
{
    dx=gw/static_cast<double>(log10(dataSize-minValueX));
    dy=gh/static_cast<double>(maxValueY-minValueY);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);
    pen.setWidth(2);
    painter.setPen(pen);

    for(int i=minValueX; i<dataSize; i++)
        painter.drawLine(QLineF(gx+log10(1+i-1)*dx, gy+(20*log10(1/data[i-1])*dy), gx+log10(1+i)*dx, gy+(20*log10(1/data[i])*dy)));
}

void Chart::drawSemiLogData(QPainter &painter, QVector<double> &data)
{
    dx=gw/static_cast<double>(log10(dataSize));
    dy=gh/(360.0/57.2);
    gmy=gy+(gh/2);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);
    pen.setWidth(2);
    painter.setPen(pen);

    for(int i=1; i<dataSize; i++)
        painter.drawLine(QLineF(gx+log10(1+i-1)*dx, gmy-(data[i-1]*dy), gx+log10(1+i)*dx, gmy-(data[i]*dy)));

}

void Chart::drawLinearGrid(QPainter &painter, QRect geometry)
{
    gx=geometry.x()+MX;
    gy=geometry.y()+MY;
    gw=geometry.width()-(2*MX);
    gh=geometry.height()-(2*MY);

    dx=gw/static_cast<double>(gridNumX);
    dy=gh/static_cast<double>(gridNumY);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(backgroundColor);
    painter.setPen(pen);
    painter.setBrush(backgroundColor);
    painter.drawRect(geometry);

    // -----  frame ------------
    pen.setStyle(Qt::SolidLine);
    pen.setColor(gridColor);
    pen.setWidth(2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(gx, gy, gw, gh);
    // ----- grid ------------
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int px=1; px<gridNumX; px++)
        painter.drawLine(QLineF(gx+(px*dx), gy, gx+(px*dx), gy+gh));
    for(int py=1; py<gridNumY; py++)
        painter.drawLine(QLineF(gx, gy+(py*dy), gx+gw, gy+(py*dy)));
    // ------ desc ----------
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    pen.setColor(textColor);
    painter.setPen(pen);
    dvx=maxValueX-minValueX;
    dvy=maxValueY-minValueY;
    for(int px=0; px<=gridNumX; px++)
        painter.drawText(QPointF(gx-(font.pointSize()/4)+px*dx, gy+gh+(font.pointSize()*2)), QString().sprintf("%d",static_cast<int>(minValueX+(dvx*px)/gridNumX)));
    for(int py=0; py<=gridNumY; py++)
        painter.drawText(QPointF(gx-(font.pointSize()*4), gy+(font.pointSize()/2)+py*dy), QString().sprintf("%4.1f",(maxValueY-(dvy*py)/gridNumY)));

}
void Chart::drawLinearData(QPainter &painter, QVector<double> &data)
{
    dx=gw/static_cast<double>(dataSize-1);
    //dy=gh/2.0;
    dy=gh/(maxValueY-minValueY);
    //gmy=gy+(gh/2);
    gmy=gy+gh;



    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=1; i<dataSize; i++)
        painter.drawLine(QLineF(gx+(i-1)*dx, gmy-(data[i-1]*dy), gx+i*dx, gmy-(data[i]*dy)));
}

void Chart::drawBarsData(QPainter &painter, QVector<double> &data)
{
    dx=gw/static_cast<double>(data.size()-0.2);
    //dy=gh/2.0;
    dy=gh/(maxValueY-minValueY);
    //gmy=gy+(gh/2);
    gmy=gy+gh;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);

    pen.setWidth(1);
    painter.setPen(pen);
    plotColor.setAlpha(128);
    painter.setBrush(plotColor);

    QFont font;
    font.setPointSize(10);
    painter.setFont(font);

    for(int i=0;i<data.size();i++){

        painter.drawRect(QRectF(gx+i*dx, gmy, 0.8*dx, -data[i]*dy));
        painter.drawText(QPointF(gx+i*dx, gmy-(font.pointSize()/2)-data[i]*dy), QString().sprintf("%4.1f [%%]", data[i]*100));
    }
}


void Chart::getMousePosition(int x, int y)
{
    dmkx=gw/static_cast<double>(maxValueX-minValueX);
    dmky=gh/static_cast<double>(maxValueY-minValueY);

    if(x<gx) x=gx;
    if(x>gx+gw) x=gx+gw;
    if(y<gy) y=gy;
    if(y>gy+gh) y=gy+gh;

    markerX=minValueX+((x-gx)/dmkx);
    markerY=maxValueY-((y-gy)/dmky);


    //qDebug()<<markerX<<markerY;

}

void Chart::drawText(QPainter &painter, int x, int y, QString text, QColor color, int size)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(backgroundColor);
    painter.setPen(pen);
    painter.setBrush(backgroundColor);

    // ------ desc ----------
    QFont font;
    font.setPointSize(size);
    painter.setFont(font);
    pen.setColor(color);
    painter.setPen(pen);
    dvx = maxValueX-minValueX;
    dvy = maxValueY-minValueY;

    painter.drawText(QPointF( x, y), text);
}

void Chart::showMarkers(QPainter &painter, QVector<double> &data)
{
    dmkx=gw/static_cast<double>(maxValueX-minValueX);
    dmky=gh/static_cast<double>(maxValueY-minValueY);

    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    painter.setPen(pen);
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);

    if(chartMode==LinearChart){

        pen.setColor(markersColorA);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx+((markerX-minValueX)*dmkx), gy, gx+((markerX-minValueX)*dmkx), gy+gh));
        painter.drawLine(QLineF(gx, gy+((maxValueY-markerY)*dmky), gx+gw, gy+((maxValueY-markerY)*dmky)));
        painter.drawText(QPointF(gx+(markerX-minValueX)*dmkx, gy-font.pointSize()), QString().sprintf("%.1f",markerX));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gy+(maxValueY-markerY)*dmky), QString().sprintf("%.1f",markerY));

        pen.setColor(markersColorB);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx, gmy-(data[static_cast<int>(markerX)-1]*dy), gx+gw, gmy-(data[static_cast<int>(markerX)-1]*dy)));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gmy-data[static_cast<int>(markerX)-1]*dy), QString().sprintf("%.1f", data[static_cast<int>(markerX)-1]));

        //qDebug()<<data[static_cast<int>(markerX)-1];
        //qDebug()<<data.size()<<static_cast<int>(markerX)-1;
    }

    if(chartMode==SemiLogChart){

        double xlog=(pow(10,(log10(dataSize)*markerX/(dataSize))));

        pen.setColor(markersColorA);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx+((markerX-minValueX)*dmkx), gy, gx+((markerX-minValueX)*dmkx), gy+gh));
        painter.drawLine(QLineF(gx, gy+((maxValueY-markerY)*dmky), gx+gw, gy+((maxValueY-markerY)*dmky)));
        painter.drawText(QPointF(gx+(markerX-minValueX)*dmkx, gy-font.pointSize()), QString().sprintf("%.1f", xlog));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gy+(maxValueY-markerY)*dmky), QString().sprintf("%.1f", markerY));

        pen.setColor(markersColorB);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx, gmy-data[static_cast<int>(xlog)-1]*dy, gx+gw, gmy-data[static_cast<int>(xlog)-1]*dy));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gmy-data[static_cast<int>(xlog)-1]*dy), QString().sprintf("%.1f", data[static_cast<int>(xlog)-1]*180));
    }

    if(chartMode==LogChart){

        double xlog=(pow(10,(log10(dataSize)*markerX/(dataSize))));

        pen.setColor(markersColorA);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx+((markerX-minValueX)*dmkx), gy, gx+((markerX-minValueX)*dmkx), gy+gh));
        painter.drawLine(QLineF(gx, gy+((maxValueY-markerY)*dmky), gx+gw, gy+((maxValueY-markerY)*dmky)));
        painter.drawText(QPointF(gx+(markerX-minValueX)*dmkx, gy-font.pointSize()), QString().sprintf("%.1f", xlog));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gy+(maxValueY-markerY)*dmky), QString().sprintf("%.1f", markerY));

        pen.setColor(markersColorB);
        painter.setPen(pen);
        painter.drawLine(QLineF(gx, gy+20*log10(1/data[static_cast<int>(xlog)-1])*dy, gx+gw, gy+20*log10(1/data[static_cast<int>(xlog)-1])*dy));
        painter.drawText(QPointF(gx+gw+font.pointSize(), gy+20*log10(1/data[static_cast<int>(xlog)-1])*dy), QString().sprintf("%.1f", -20*log10(1/data[static_cast<int>(xlog)-1])));
    }
}
