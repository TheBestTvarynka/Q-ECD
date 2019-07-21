#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "data/datafigures.h"
#include "modes/modeinterface.h"
#include "modes/objectmode.h"
#include "modes/drawcablemode.h"

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
    QPoint Center;
    // temp variavle. use when we drag a mouse
    QPoint start_position;
public:
    PaintBoard(QWidget *parent = 0, ModeInterface *start_state = nullptr);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

    double GetScale() { return Scale; }
    QPoint GetCenter() { return mode->GetCenter(); }

    DataFigures *GetDataFigures() { return &figures; }
    void SetMode(ModeInterface *);
};

#endif // PAINTBOARD_H
