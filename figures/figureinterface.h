#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include <math.h>
#include <QMap>
#include "figures/iobservable.h"

typedef QPoint (*GetClampCoordinates)(int, int);

class FigureInterface : public IObservable
{
protected:
    double x, y;
    double main_color[3];
    QMap<int, QPoint (*)(int, int)> clamp_coordiantes;
public:
    FigureInterface() : x(10.0), y(10.0) {}
    FigureInterface(int X, int Y);
    virtual void print(double) = 0;
    virtual QPoint SelectClamp(QPoint) = 0;
    double GetX() { return x; }
    double GetY() { return y; }
    void SetMainColor(double [3]);
    void SetPosition(double, double);
    void MoveFigure(double, double);
};

#endif // FIGUREINTERFACE_H
