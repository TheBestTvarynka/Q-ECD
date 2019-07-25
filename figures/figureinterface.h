#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include <math.h>
#include <QMap>
#include "figures/iobservable.h"

typedef QPoint (*GetClampCoordinates)(int, int);

using std::pair;

class FigureInterface : public IObservable
{
protected:
    double x, y;
    double main_color[3];
    QMap<int, GetClampCoordinates> clamp_coordiantes;
public:
    FigureInterface() : x(10.0), y(10.0) {}
    FigureInterface(int X, int Y);
    virtual void print(double) = 0;
    pair<int, double> SelectClamp(QPoint, double, QMap<int, GetClampCoordinates>);
    double GetX() { return x; }
    double GetY() { return y; }
    QMap<int, GetClampCoordinates> GetClams() { return clamp_coordiantes; }
    QPoint GetClamp(int clamp) { return (*clamp_coordiantes[clamp])(int(x), int(y));}
    void SetMainColor(double [3]);
    void SetPosition(double, double);
    void MoveFigure(double, double);
};

#endif // FIGUREINTERFACE_H
