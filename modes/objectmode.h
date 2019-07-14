#ifndef OBJECTMODE_H
#define OBJECTMODE_H

#include <QDebug>
#include "modeinterface.h"

class ObjectMode : public ModeInterface
{
public:
    explicit ObjectMode(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(double, int, int);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // OBJECTMODE_H
