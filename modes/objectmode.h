#ifndef OBJECTMODE_H
#define OBJECTMODE_H

#include <QDebug>
#include "modeinterface.h"

class ObjectMode : public ModeInterface
{
    QPoint start_position;
public:
    explicit ObjectMode(PaintBoard *, double, QPoint, int, int);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(QPoint &);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // OBJECTMODE_H
