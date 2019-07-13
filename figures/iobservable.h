#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <QVector>

using std::pair;

class IObservable
{
protected:
    QVector<pair<int *, bool> > connections;
public:
    IObservable();
    void Register(int *, bool);
    void Remove();
};

#endif // IOBSERVABLE_H
