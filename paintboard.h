#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "data/datafigures.h"
#include "modes/modeinterface.h"
#include "modes/objectmode.h"

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>

using std::pair;

class PaintBoard : public QGLWidget
{
    Q_OBJECT
    QTimer mpTimer;
    ModeInterface *mode;
    DataFigures figures;

    int CenterX, CenterY;
    QPoint Delta;
    double Scale;

    QPoint start_position;
public:
    PaintBoard(QWidget *parent = 0, ModeInterface *start_state = nullptr);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // PAINTBOARD_H
