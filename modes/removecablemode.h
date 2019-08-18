#ifndef REMOVECABLEMODE_H
#define REMOVECABLEMODE_H

#include "modeinterface.h"

#include <QDebug>

using std::pair;

class RemoveCableMode : public ModeInterface
{
    QPoint start_position;
    Qt::MouseButton click;

    pair<QPoint, QPoint> line;
public:
    explicit RemoveCableMode(PaintBoard *, double, QPoint, int, int);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(QPoint &);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // REMOVECABLEMODE_H
