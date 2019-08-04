#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QMap>

class IObservable;

class IObserver
{
    QMap<IObservable *, int> connections;
public:
    IObserver();
    IObserver(IObservable *parent, int vertex);
    virtual void update(IObservable *, double, double) = 0;
    void AddObservable(IObservable *parent, int vertex);
    int GetVertex(IObservable *p) { return connections[p]; }
};

#endif // IOBSERVER_H
