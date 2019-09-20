#ifndef DATACABLES_H
#define DATACABLES_H

#include <QVector>
#include <QList>

#include "cables/iobserver.h"
#include "cables/cable.h"

class DataCables : public QObject
{
    Q_OBJECT

    QVector<Cable *> cables;
    QList<Cable *> selected;
public:
    DataCables();
    void AddCable(Cable *);
    bool RemoveCable(Cable *);
    void InsertVertex(Cable *, double, double);
    void RemoveLoop(Cable *, QPoint, double);
    void ClearSelected() { selected.clear(); }
    void RemoveFromSelected(QList<Cable *>);
    void AddToSelected(QList<Cable *>);
    Cable *GetLast() { return cables.back(); }
    QList<Cable *> GetForDeleting(pair<QPoint, QPoint>,  double);
    QList<Cable *> GetForDeleting(QPoint,  double);
    QList<Cable *> GetSelectedCables() { return selected; }
    QVector<Cable *> GetCables() { return cables; }
    void SetCablesColor(QList<Cable *>, QColor);
    void SetSelected(QList<Cable *> s) { selected = s; }
public slots:
    void RemoveCables(QList<IObserver *>);
    void RemoveCables(QList<Cable *>);
    void RemoveSelectedCables();
};

#endif // DATACABLES_H
