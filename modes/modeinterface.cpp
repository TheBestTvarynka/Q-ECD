#include "modeinterface.h"
#include "paintboard.h"
#include <QDebug>
#include "paintboard.h"

ModeInterface::ModeInterface(double s, PaintBoard *p, QWidget *parent)
{
    Parent = p;
    scale = s;
}

void ModeInterface::ScaleEvent(bool zoom, QPoint mouse, double &Scale)
{
//    qDebug() << (-54) % (23);
    QPoint new_Center;

    int n = int((mouse.x() - Center.x()) / Scale);
//    qDebug() << "n: " << n;
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
    resizeGL(Weight, Height);
}
