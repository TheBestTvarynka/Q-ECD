#ifndef CABLE_H
#define CABLE_H

#include <QVector>
#include <QPoint>

class Cable
{
    QVector<QPoint> points;
public:
    Cable(int, int);
    void print(double);
};

#endif // CABLE_H
