#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>

class ModeInterface : public QGLWidget
{
protected:
    Q_OBJECT
public:
    explicit ModeInterface(QWidget *parent = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    virtual void paintGL() = 0;
    virtual void mousePressEvent(QMouseEvent *) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
};

#endif // MODEINTERFACE_H
