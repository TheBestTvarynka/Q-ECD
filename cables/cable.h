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
    double main_color[3];
public:
    Cable(int, int);
    void print(double);
    void update(IObservable *, double, double);
    void insert_back(double, double);
    void RemoveLoops(QPoint, double);
    bool CheckIntersection(pair<QPoint, QPoint>, double);
    bool CheckIntersection(QPoint, double);
    bool CheckState(pair<double, double>, pair<double, double>);
    bool IsMarked();
    pair<double, double> *GetLastPoint() { return &points.back(); }
    int GetSize() { return points.size(); }
    pair<double, double> GetPoint(int i) { return points[i]; }
//    void MovePoint(int, double, double);
    void SetPoint(int i, double X, double Y);
    void SetMainColor(double [3]);
};

#endif // CABLE_H
