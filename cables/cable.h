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
    QColor main_color;
    QMap<QString, QVector<QVariant> > data;
public:
    Cable(int, int);
    void update(IObservable *, double, double);
    void insert_back(double, double);
    void RemoveLoops(QPoint, double);
    bool CheckIntersection(pair<QPoint, QPoint>, double);
    bool CheckIntersection(QPoint, double);
    bool CheckState(pair<double, double>, pair<double, double>);
    bool CheckState(int, int);
    bool IsMarked();
    void BuilData();
    int GetSize() { return points.size(); }
    pair<double, double> GetPoint(int i) { return points[i]; }
    QMap<QString, QVector<QVariant> > GetData() { return data; }
    QColor GetColor() { return main_color; }
    void SetPoint(int, double, double);
    void SetPoint(int, QPoint);
    void SetMainColor(QColor);
};

#endif // CABLE_H
