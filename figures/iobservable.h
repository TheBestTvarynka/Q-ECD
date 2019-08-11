#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <QVector>
#include <QMap>
#include "cables/iobserver.h"

class IObservable
{
protected:
    QMap<IObserver*, int> connections;
public:
    IObservable();
    void Register(IObserver *, int);
    void Remove(IObserver *);
    void RemoveAll();
    virtual void Notify() = 0;
};

#endif // IOBSERVABLE_H
