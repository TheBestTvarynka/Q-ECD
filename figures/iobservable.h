#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <QVector>

#include "cables/iobserver.h"

struct Connector
{
    IObserver *cable;
    int vertex;
    int clamp;
    Connector(IObserver *cb, int v, int cl)
    {
        cable = cb;
        vertex = v;
        clamp = cl;
    }
    Connector()
    {
        cable = nullptr;
        vertex = clamp = -1;
    }
};

class IObservable
{
protected:
    QVector<Connector> connections;
public:
    IObservable();
    void Register(IObserver *, int, int);
    void Remove();
    void Notify();
};

#endif // IOBSERVABLE_H
