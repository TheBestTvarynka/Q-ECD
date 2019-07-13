#include "iobservable.h"

IObservable::IObservable()
{
    // start connection
}

void IObservable::Register(int *obj, bool se)
{
    connections.push_back(pair<int *, bool>(obj, se));
}

void IObservable::Remove()
{
    // remove
}
