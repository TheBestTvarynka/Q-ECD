#ifndef FIGURECREATOR_H
#define FIGURECREATOR_H

#include <QString>
#include <QMap>
#include <QPoint>
#include <QPointF>
#include <QVariant>

using std::function;

class FigureCreator
{
    typedef QMap<QString, QVector<QVariant> > (FigureCreator::*DataGenerator)(double, double, QString);
    typedef QMap<int, function<QPointF (double, double)> > (FigureCreator::*ClampGenerator)();
    QMap<QString, ClampGenerator> CLAMP;
    QMap<QString, DataGenerator> DATA;
public:
    FigureCreator();
    QMap<QString, QVector<QVariant> > GetFigureData(QString type, double x, double y, QString name) { return (this->*DATA[type])(x, y, name); }
    QMap<int, function<QPointF (double, double)> > GetFigureClamp(QString type) { return (this->*CLAMP[type])(); }
    // simple resistor
    QMap<QString, QVector<QVariant> > ResistorData(double, double, QString);
    QMap<int, function<QPointF (double, double)> > ResistorClamp();
    // simple capasitor
    QMap<QString, QVector<QVariant> > CapacitorData(double, double, QString);
    QMap<int, function<QPointF (double, double)> > CapacitorClamp();
    //
};

#endif // FIGURECREATOR_H
