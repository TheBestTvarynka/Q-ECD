#ifndef DATACABLES_H
#define DATACABLES_H

#include <QVector>

#include "cables/iobserver.h"
#include "cables/cable.h"

class DataCables
{
    QVector<Cable *> cables;
    QList<Cable *> selected;
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
    void ClearSelected() { selected.clear(); }
    Cable *GetLast() { return cables.back(); }
    pair<double, double> *GetLastPoint(Cable *c) { return c->GetLastPoint(); }
    QList<Cable *> GetForDeleting(pair<QPoint, QPoint>,  double);
    QList<Cable *> GetForDeleting(QPoint,  double);
    void SetPoint(pair<double, double> &, pair<double, double>);
    void SetSelected(QList<Cable *> s) { selected = s; }
    bool GetDirectionEnd(Cable *);
    QList<Cable *> GetSelectedCables() { return selected; }
};

#endif // DATACABLES_H
