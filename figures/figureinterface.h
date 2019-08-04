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

class FigureInterface : public IObservable
{
protected:
    double x, y;
    QString name;
    double nameX, nameY;
    double main_color[3];
    QMap<int, GetClampCoordinates> clamp_coordiantes;
public:
    FigureInterface() : x(10.0), y(10.0), name("R1") {}
    FigureInterface(int X, int Y, QString n);
    virtual void print(double, PaintBoard *) = 0;
    void Notify();
    pair<int, double> SelectClamp(QPoint, double, QMap<int, GetClampCoordinates>);
    void MoveFigure(double, double);
    double GetX() { return x; }
    double GetY() { return y; }
    QMap<int, GetClampCoordinates> GetClams() { return clamp_coordiantes; }
    pair<double, double> GetClamp(int clamp) { return (*clamp_coordiantes[clamp])(x, y);}
    void SetMainColor(double [3]);
    void SetPosition(double, double);
};

#endif // FIGUREINTERFACE_H
