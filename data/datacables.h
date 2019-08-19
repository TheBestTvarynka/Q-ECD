#ifndef DATACABLES_H
#define DATACABLES_H

#include <QVector>

#include "cables/iobserver.h"
#include "cables/cable.h"

class DataCables
{
    QVector<Cable *> cables;
public:
    DataCables();
    void AddCable(Cable *);
    bool RemoveCable(Cable *);
    void RemoveCables(QList<IObserver *>);
    void RemoveCables(QList<Cable *>);
    void print(double);
    void SetCablesColor(QList<Cable *>, double [3]);
    void InsertVertex(Cable *, double, double);
    void RemoveLoop(Cable *, QPoint, double);
    Cable *GetLast() { return cables.back(); }
    pair<double, double> *GetLastPoint(Cable *c) { return c->GetLastPoint(); }
    QList<Cable *> GetForDeleting(pair<QPoint, QPoint>,  double);
    QList<Cable *> GetForDeleting(QPoint,  double);
    void SetPoint(pair<double, double> &, pair<double, double>);
    bool GetDirectionEnd(Cable *);
};

#endif // DATACABLES_H
