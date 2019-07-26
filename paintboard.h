#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "data/datafigures.h"
#include "modes/modeinterface.h"
#include "modes/objectmode.h"

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>

using std::pair;

class PaintBoard : public QGLWidget
{
    Q_OBJECT
    QTimer mpTimer;

    ModeInterface *mode;
    DataFigures figures;

    QPoint Delta;
    double Scale;
    // temp variavle. use when we drag a mouse
    QPoint start_position;
    Qt::MouseButton click;
public:
    PaintBoard(QWidget *parent = 0, ModeInterface *start_state = nullptr);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

    DataFigures *GetDataFigures() { return &figures; }
};

#endif // PAINTBOARD_H
