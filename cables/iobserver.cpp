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

void IObserver::RmoveObservable(IObservable *parent)
{
    connections.remove(parent);
}

IObserver::~IObserver()
{

}
