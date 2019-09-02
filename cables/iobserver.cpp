#include "iobserver.h"
#include "figures/iobservable.h"

IObserver::IObserver()
{

}

IObserver::IObserver(IObservable *parent, int vertex)
{
    AddObservable(parent, vertex);
}

void IObserver::AddObservable(IObservable *parent, int vertex)
 {
    connections.insert(parent, vertex);
}

void IObserver::RemoveObservable(IObservable *parent)
{
    connections.remove(parent);
}

void IObserver::RemoveAllObservable()
{
    QMapIterator<IObservable*, int> it(connections);
    while (it.hasNext())
    {
        it.next();
        it.key()->Remove(this);
    }
    connections.clear();
}

bool IObserver::isConnected(IObservable *f)
{
    QMapIterator<IObservable*, int> it(connections);
    while (it.hasNext())
    {
        it.next();
        if (it.key() == f)
            return true;
    }
    return false;
}

IObserver::~IObserver()
{

}
