#include "iobservable.h"

IObservable::IObservable()
{
    // start connection
}

void IObservable::Register(Cable *cable, int vertex, int clamp)
{
    connections.push_back(Connector(cable, vertex, clamp));
}

void IObservable::Remove()
{
    // remove
}
