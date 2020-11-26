#ifndef CHART_H
#define CHART_H

#include "pre_headers.h"

#define MX      40
#define MY      40
#define LOGMAX  50

enum ChartMode {
    LinearChart,
    LogChart,
    SemiLogChart
};

class Chart
{
public:
    Chart();

    void drawLogGrid(QPainter &painter, QRect geometry);
    void drawLogData(QPainter &painter, QVector<double> &data);
    void drawSemiLogData(QPainter &painter, QVector<double> &data);
    void drawLinearGrid(QPainter &painter, QRect geometry);
    void drawLinearData(QPainter &painter, QVector<double> &data);
    void drawBarsData(QPainter &painter, QVector<double> &data);
    void showMarkers(QPainter &painter, QVector<double> &data);
    void getMousePosition(int x, int y);
    void drawText(QPainter &painter, int x, int y, QString text, QColor color = Qt::white, int size_8 = 8);

    int gridNumX=10, gridNumY=10;
    int minValueX=0, maxValueX=100;
    int minValueY=-100, maxValueY=100;
    int chartMode=0;
    double markerX=1, markerY=0;
    int dataSize;

    QColor backgroundColor=Qt::black;
    QColor gridColor=Qt::gray;
    QColor textColor=Qt::white;
    QColor plotColor=Qt::cyan;
    QColor markersColorA=Qt::red;
    QColor markersColorB=Qt::yellow;

private:
    double dx, dy, dvx, dvy, dmkx, dmky;
    int gx, gy, gw, gh, gmy;
    double logTable[LOGMAX];

};

#endif // CHART_H
