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
    void print(double);
    void InsertVertex(Cable *, double, double);
    Cable *GetLast() { return cables.back(); }
    pair<double, double> *GetLastPoint(Cable *c) { return c->GetLastPoint(); }
    void SetPoint(pair<double, double> &, pair<double, double>);
    bool GetDirectionEnd(Cable *);
};

#endif // DATACABLES_H
