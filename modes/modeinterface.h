#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>

class PaintBoard;

class ModeInterface
{
public:
    PaintBoard *Parent;
    int Weight, Height;
    QPoint Center;
    double scale;

    explicit ModeInterface(double, PaintBoard *, int, int);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    virtual void paintGL(QPoint &) = 0;
    virtual void mousePressEvent(QMouseEvent *) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *);

    QPoint RoundCoordinates(double, double);
    void ScaleEvent(bool, QPoint, double &);
    QPoint GetCenter() { return Center; }

    virtual ~ModeInterface();
};

#endif // MODEINTERFACE_H
