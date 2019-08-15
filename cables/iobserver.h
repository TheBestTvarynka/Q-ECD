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
    void AddObservable(IObservable *parent, int vertex = 0);
    void RemoveObservable(IObservable *);
    void RemoveAllObservable();
    int GetVertex(IObservable *p) { return connections[p]; }
    virtual ~IObserver() = 0;
};

#endif // IOBSERVER_H
