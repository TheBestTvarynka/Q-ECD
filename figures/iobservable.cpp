#include "iobservable.h"

IObservable::IObservable()
{
    // start connection
}

void IObservable::Register(IObserver *new_observer, int clamp)
{
    connections.insert(new_observer, clamp);
}

void IObservable::Remove(IObserver *new_observer)
{
//    QMapIterator<IObserver* const, IObserver* const> it(connections);
    connections.remove(new_observer);
}

void IObservable::RemoveAll()
{
    foreach (IObserver *i, connections.keys())
    {
        i->RemoveObservable(this);
        connections.remove(i);
    }
}

QList<IObserver *> IObservable::GetIObservers()
{
    QList<IObserver *> obs;
    foreach (IObserver *i, connections.keys())
    {
        obs.append(i);
    }
    return obs;
}

IObservable::~IObservable()
{

}
