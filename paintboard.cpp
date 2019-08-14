#include "paintboard.h"
#include <QDebug>

PaintBoard::PaintBoard(QWidget *parent, ModeInterface *start_state): QGLWidget(parent)
{
    Scale = 20;
    Delta.setX(0);
    Delta.setY(0);
    click = Qt::MouseButton::NoButton;

    connect(&mpTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mpTimer.start(10);

    if (start_state == nullptr)
        mode = new ObjectMode(this, Scale, QPoint(0, 0), width(), height());
//    figures.add(new Resistor(5, 7, "R1"));
//    figures.add(new Capacitor(4, 3, "C1"));
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
    mode->paintGL(Delta);
}

void PaintBoard::mousePressEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        start_position = ap->pos();
        click = Qt::MouseButton::MidButton;
    }
    else
    {
        mode->mousePressEvent(ap);
    }
}

void PaintBoard::mouseMoveEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        Delta = ap->pos() - start_position;
        start_position = ap->pos();
    }
    else
    {
        mode->mouseMoveEvent(ap);
    }
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *ap)
{
    if (click == Qt::MidButton)
    {
        click = Qt::MouseButton::NoButton;
    }
    else
    {
        mode->mouseReleaseEvent(ap);
    }
}

void PaintBoard::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        mode->ScaleEvent(true, event->pos(), Scale);
    else
        mode->ScaleEvent(false, event->pos(), Scale);
}

void PaintBoard::RenderText(pair<double, double> point, double rotation, QString text)
{
    glPushMatrix();
    glTranslated(point.first * Scale, point.second * Scale, 0.0);
    glRotated(rotation, 0.0, 0.0, 1.1);
    renderText(mode->GetCenter().x() + int(point.first * Scale), mode->GetCenter().y() + int(point.second * Scale), text, QFont("Arial", int(Scale * 0.67), 5, false));
    glColor3d(0.0, 0.0, 0.0);
//    glPointSize(40);
//    glBegin(GL_POINTS);
//    glVertex2f(float(0), float(0));
//    glEnd();

    renderText(0, 0, text, QFont("Arial", int(Scale * 0.67), 5, false));
    glPopMatrix();
}

void PaintBoard::SetMode(ModeInterface *newMode)
{
    delete mode;
    mode = newMode;
}

void PaintBoard::SetSelectedFigure(FigureInterface *f)
{
    figures.SetSelectedFigure(f);
    emit LoadFigurePropereties(f->GetName(), f->GetValue());
}

void PaintBoard::CreateFigure(int f)
{
    FigureInterface *new_figure = creator.GetNewFigure(f, int((width() / 2 - mode->GetCenter().x()) / Scale), int((height() / 2 - mode->GetCenter().y()) / Scale), "F" + QString::number(figures.size()), "vl");
    figures.add(new_figure);
    emit AddToTree(new_figure);
}

void PaintBoard::RemoveSelectedFigure()
{
    figures.erase(figures.GetSelectedFigure());
}

void PaintBoard::RotateSelectedFigureRight()
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    selected->Rotate(90);
    selected->Notify();
}

void PaintBoard::RotateSelectedFigureLeft()
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    selected->Rotate(-90);
    selected->Notify();
}
