#ifndef OBJECTMODE_H
#define OBJECTMODE_H

#include <QDebug>
#include "modeinterface.h"

class ObjectMode : public ModeInterface
{
    QPoint start_position;
    Qt::MouseButton click;
public:
    explicit ObjectMode(PaintBoard *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // OBJECTMODE_H
