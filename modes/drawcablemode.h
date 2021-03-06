#ifndef DRAWCABLEMODE_H
#define DRAWCABLEMODE_H

#include <QDebug>
#include "modeinterface.h"

class DrawCableMode : public ModeInterface
{
    QPoint start_position;
    Qt::MouseButton click;
public:
    explicit DrawCableMode(PaintBoard *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // DRAWCABLEMODE_H
