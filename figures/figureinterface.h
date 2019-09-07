#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include <math.h>
#include <QMap>
#include <QString>
#include <QVariant>
#include "figures/iobservable.h"

using std::pair;
using std::function;

typedef pair<double, double> (*GetClampCoordinates)(double, double);

class PaintBoard;
class QTreeItem;

class FigureInterface : public IObservable
{
protected:
    double x, y;
    int rotation;
    QString name;
    QString value;
    double nameX, nameY;
    QColor main_color;
    QTreeItem *treeItem;
    QMap<int, GetClampCoordinates> clamp_coordiantes;
    QString type;

    QMap<QString, QVector<QVariant> > data;
    QMap<int, function<QPointF (double, double)> > clamp;
public:
    FigureInterface(int X,
                    int Y,
                    int R,
                    QString n,
                    QString v,
                    QString t);
    FigureInterface(const FigureInterface *);

    void Notify();
    pair<int, double> SelectClamp(QPoint, double);
    void MoveFigure(double, double);
    double GetX() { return x; }
    double GetY() { return y; }
    pair<double, double> GetPos() { return pair<double, double>(x, y); }
    int GetRotation() { return rotation; }
    QString GetName() { return name; }
    QString GetValue() { return value; }
    QString GetType() { return type; }
    QMap<int, GetClampCoordinates> GetClams() { return clamp_coordiantes; }
    pair<double, double> GetClampp(int clamp) { return RotatePoint((*clamp_coordiantes[clamp])(x, y), rotation); } // bad code
    QPointF GetClamp(int c) { return RotatePoint(clamp[c](x, y), rotation); }
    QMap<QString, QVector<QVariant> > GetData() { return data; }
    QColor GetColor() { return main_color; }
    void SetData(QMap<QString, QVector<QVariant> > d) { data = d; }
    void SetClamp(QMap<int, function<QPointF (double, double)> > c) { clamp = c; }
    void SetMainColor(QColor);
    void SetPosition(double, double);
    void SetTreeItem(QTreeItem *item) { treeItem = item; }
    void SetName(QString Name);
    void SetValue(QString Value);
    void Rotate(double);
    void DeleteTreeItem();
    pair<double, double> RotatePoint(pair<double, double>, double);
    QPointF RotatePoint(QPointF, double);
};

#endif // FIGUREINTERFACE_H
