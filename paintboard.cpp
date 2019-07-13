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
