#ifndef CABLE_H
#define CABLE_H

#include <QGLWidget>
#include <QVector>
#include <QPoint>

using std::pair;
#include "cables/iobserver.h"


class Cable : IObserver
{
    QVector<pair<double, double> > points;
public:
    Cable(int, int);
    void print(double);
    void update();
    void insert_back(double, double);
    pair<double, double> *GetLastPoint() { return &points.back(); }
    int GetSize() { return points.size(); }
    pair<double, double> GetPoint(int i) { return points[i]; }
};

#endif // CABLE_H
