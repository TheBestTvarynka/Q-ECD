#ifndef CABLE_H
#define CABLE_H

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
};

#endif // CABLE_H
