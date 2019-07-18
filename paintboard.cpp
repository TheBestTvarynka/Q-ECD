#include "paintboard.h"

PaintBoard::PaintBoard(QWidget *parent, ModeInterface *start_state): QGLWidget(parent)
{
    Scale = 20;
    Delta.setX(0);
    Delta.setY(0);

    connect(&mpTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mpTimer.start(10);

    if (start_state == nullptr)
        mode = new ObjectMode;
}

void PaintBoard::initializeGL()
{
    mode->initializeGL();
}

void PaintBoard::resizeGL(int w, int h)
{
    mode->resizeGL(w, h);
}

void PaintBoard::paintGL()
{
    mode->paintGL(Scale, Delta);
    figures.print();
}

void PaintBoard::mousePressEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        start_position = ap->pos();
    }
    mode->mousePressEvent(ap);
}

void PaintBoard::mouseMoveEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        Delta = ap->pos() - start_position;
        start_position = ap->pos();
    }
    mode->mouseMoveEvent(ap);
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *ap)
{
    mode->mouseReleaseEvent(ap);
}

void PaintBoard::wheelEvent(QWheelEvent *event)
{
    qDebug() << "Whell Event: " << event->angleDelta();
    if (event->angleDelta().y() > 0)
        mode->ScaleEvent(true, event->pos(), Scale);
    else
        mode->ScaleEvent(false, event->pos(), Scale);
}
