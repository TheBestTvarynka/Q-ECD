#include "modeinterface.h"
#include "paintboard.h"
#include <QDebug>

ModeInterface::ModeInterface(PaintBoard *p)
{
    Parent = p;
    color.setRgb(135, 65, 23);
}

void ModeInterface::keyPressEvent(QKeyEvent *)
{

}

void ModeInterface::keyReleaseEvent(QKeyEvent *)
{

}

QPoint ModeInterface::RoundCoordinates(double X, double Y)
{
    QPoint Result;
    double rest = X - int(X);
    if (rest >= 0.5)
        Result.setX(int(X) + 1);
    else
        Result.setX(int(X));
    rest = Y - int(Y);
    if (rest >= 0.5)
        Result.setY(int(Y) + 1);
    else
        Result.setY(int(Y));
    return Result;
}

ModeInterface::~ModeInterface()
{

}
