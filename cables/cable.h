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
};

#endif // CABLE_H
