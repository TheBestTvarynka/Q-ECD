#include "iobservable.h"

IObservable::IObservable()
{
    // start connection
}

void IObservable::Register(IObserver *new_observer)
{
    connections.insert(new_observer, new_observer);
}

void IObservable::Remove(IObserver *new_observer)
{
//    QMapIterator<IObserver* const, IObserver* const> it(connections);
    connections.remove(new_observer);
}
