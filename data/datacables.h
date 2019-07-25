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
};

#endif // DATACABLES_H
