#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <QVector>
#include <QMap>
#include "cables/iobserver.h"
#include <QList>

class IObservable
{
protected:
    QMap<IObserver*, int> connections;
public:
    IObservable();
    void Register(IObserver *, int);
    void Remove(IObserver *);
    void RemoveAll();
    QList<IObserver *> GetIObservers();
    virtual void Notify() = 0;
    virtual ~IObservable();
};

#endif // IOBSERVABLE_H
