#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
    int observable;
public:
    IObserver();
    virtual void update() = 0;
    void SetObservable(int o) { observable = o; }
};

#endif // IOBSERVER_H
