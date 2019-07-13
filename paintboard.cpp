#include "paintboard.h"

PaintBoard::PaintBoard(QWidget *parent, ModeInterface *start_state): QGLWidget(parent)
{
    connect( &mpTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mpTimer.start(10);
    if (start_state == nullptr)
    {
        mode = new ObjectMode;
    }
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
    mode->paintGL();
    figures.print();
}

void PaintBoard::mousePressEvent(QMouseEvent *ap)
{
    mode->mousePressEvent(ap);
}

void PaintBoard::mouseMoveEvent(QMouseEvent *ap)
{
    mode->mouseMoveEvent(ap);
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *ap)
{
    mode->mouseReleaseEvent(ap);
}
