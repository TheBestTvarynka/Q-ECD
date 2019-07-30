#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <QVector>
#include <QMap>
#include "cables/iobserver.h"

class IObservable
{
protected:
    QMap<IObserver* const, IObserver* const> connections;
public:
    IObservable();
    void Register(IObserver *);
    void Remove(IObserver *);
    virtual void Notify() = 0;
};

#endif // IOBSERVABLE_H
