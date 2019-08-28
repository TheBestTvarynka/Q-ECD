#include "modeinterface.h"
#include "paintboard.h"
#include <QDebug>

ModeInterface::ModeInterface(double s, PaintBoard *p, int w, int h)
{
    Parent = p;
    scale = s;
    Weight = w;
    Height = h;
}

void ModeInterface::keyPressEvent(QKeyEvent *event)
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

void ModeInterface::ScaleEvent(bool zoom, QPoint mouse, double &Scale)
{
    QPoint new_Center;

    int n = int((mouse.x() - Center.x()) / Scale);
    double new_Scale = 10.0;
    double k = mouse.x() - Center.x() - n * Scale;
    if (zoom) {
        k *= 1.1;
        new_Scale = Scale * 1.1;
    } else {
        k *= 0.9;
        new_Scale = Scale * 0.9;
    }
    new_Center.setX( int(mouse.x() - new_Scale * n - k) );

    n = int((mouse.y() - Center.y()) / Scale);
    k = mouse.y() - Center.y() - n * Scale;
    if (zoom) {
        k *= 1.1;
    } else {
        k *= 0.9;
    }
    new_Center.setY( int(mouse.y() - new_Scale * n - k) );
    scale = Scale = new_Scale;

//    qDebug() << "zoom: " << zoom;
//    qDebug() << new_Center.x() << " " << new_Center.y();
//    glTranslated(new_Center.x() - Center.x(), new_Center.y() - Center.y(), 0);
    Center = new_Center;
    Parent->resizeGL(Weight, Height);
}

ModeInterface::~ModeInterface()
{

}
