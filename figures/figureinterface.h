#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include <math.h>
#include <QMap>
#include <QString>
#include "figures/iobservable.h"

using std::pair;

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
    double main_color[3];
    QTreeItem *treeItem;
    QMap<int, GetClampCoordinates> clamp_coordiantes;
public:
    FigureInterface() : x(10.0), y(10.0), rotation(0), name("R1") {}
    FigureInterface(int X, int Y, QString n, QString v);
    FigureInterface(const FigureInterface *);

    virtual void print(double, PaintBoard *) = 0;
    void Notify();
    pair<int, double> SelectClamp(QPoint, double, QMap<int, GetClampCoordinates>);
    void MoveFigure(double, double);
    double GetX() { return x; }
    double GetY() { return y; }
    QString GetName() { return name; }
    QString GetValue() { return value; }
    QMap<int, GetClampCoordinates> GetClams() { return clamp_coordiantes; }
    pair<double, double> GetClamp(int clamp) { return RotatePoint((*clamp_coordiantes[clamp])(x, y), rotation); }
    void SetMainColor(double [3]);
    void SetPosition(double, double);
    void SetTreeItem(QTreeItem *item) { treeItem = item; }
    void SetName(QString Name);
    void SetValue(QString Value);
    void Rotate(double);
    void DeleteTreeItem();
    pair<double, double> RotatePoint(pair<double, double>, double);
};

#endif // FIGUREINTERFACE_H
