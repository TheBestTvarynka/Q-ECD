#ifndef CABLE_H
#define CABLE_H

#include <QGLWidget>
#include <QVector>
#include <QPoint>
#include <math.h>

using std::pair;
#include "cables/iobserver.h"


class Cable : public IObserver
{
    QVector<pair<double, double> > points;
public:
    Cable(int, int);
    void print(double);
    void update(IObservable *, double, double);
    void insert_back(double, double);
    void RemoveLoops(QPoint, double);
    pair<double, double> *GetLastPoint() { return &points.back(); }
    int GetSize() { return points.size(); }
    pair<double, double> GetPoint(int i) { return points[i]; }
//    void MovePoint(int, double, double);
    void SetPoint(int i, double X, double Y);
};

#endif // CABLE_H
