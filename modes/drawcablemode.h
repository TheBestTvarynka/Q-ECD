#ifndef DRAWCABLEMODE_H
#define DRAWCABLEMODE_H

#include <QDebug>
#include "modeinterface.h"

class DrawCableMode : public ModeInterface
{
    QPoint start_position;
public:
    explicit DrawCableMode(PaintBoard *, double, QPoint, QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(QPoint &);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // DRAWCABLEMODE_H
