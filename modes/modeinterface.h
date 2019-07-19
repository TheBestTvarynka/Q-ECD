#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>

class PaintBoard;

class ModeInterface : public QGLWidget
{
protected:
    Q_OBJECT
public:
    PaintBoard *Parent;
    int Weight, Height;
    QPoint Center;
    explicit ModeInterface(PaintBoard *, QWidget *parent = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    virtual void paintGL(double, QPoint &) = 0;
    virtual void mousePressEvent(QMouseEvent *, double) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;

    void ScaleEvent(bool, QPoint, double &);
};

#endif // MODEINTERFACE_H
