#ifndef DATAFIGURES_H
#define DATAFIGURES_H

#include <QVector>
#include <QList>
#include <math.h>
#include "cables/iobserver.h"
#include "figures/figureinterface.h"
//#include "figures/figurecreator.h"

class PaintBoard;

class DataFigures : public QObject
{
    Q_OBJECT

    QVector<FigureInterface *> figures;
    FigureInterface *selected_figure;
    int selected_clamp;
public:
    DataFigures();
    void add(FigureInterface *);
    QList<IObserver *> erase(FigureInterface *);
    void select_figure(QPoint, double);
    void MoveSelectedFigure(FigureInterface *, double, double);
    void RoundCoordinates(FigureInterface *);
    void Register(FigureInterface *, int, IObserver *, int);
    FigureInterface *GetSelectedFigure();
    QVector<FigureInterface *> GetFigures() { return figures; }
    pair<FigureInterface *, int> SelectClamp(QPoint, double);
    int size() { return figures.size(); }
public slots:
    void SetSelectedFigure(FigureInterface *);
    void RemoveSelectedFigure();
    void SetNameSelectedFigure(const QString &);
    void SetValueSelectedFigure(const QString &);
    void RotateSelectedFigureRight();
    void RotateSelectedFigureLeft();
signals:
    void ClearPropereties();
    void RemoveCables(QList<IObserver *>);
    void LoadFigurePropereties(QString, QString);
};

#endif // DATAFIGURES_H
