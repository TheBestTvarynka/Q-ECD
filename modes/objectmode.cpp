#include "objectmode.h"
#include "paintboard.h"

ObjectMode::ObjectMode(PaintBoard *p, QWidget *parent) : ModeInterface (p, parent) { Center = QPoint(0, 0);}

void ObjectMode::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void ObjectMode::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);

    Weight = w;
    Height = h;
}
void ObjectMode::paintGL(double Scale, QPoint &Delta)
{
    QColor background(220, 220, 220, 255);
    qglClearColor(background);
//    qglClearColor(Qt::gray);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    // enable alfa
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTranslated(Delta.x(), Delta.y(), 0);
    Center += Delta;
    Delta = QPoint(0, 0);

    glColor3d(0.0, 0.0, 1);

    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(Scale / 10));
    glBegin(GL_POINTS);

    int nV = int(Weight / Scale) + 1;
    int nH = int(Height / Scale) + 1;
    double DeltaX = Center.x() - int(Center.x() / Scale) * Scale, DeltaY = Center.y() - int(Center.y() / Scale) * Scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * Scale - Center.x() + DeltaX), float(i * Scale - Center.y() + DeltaY));
        }
    }
    glEnd();
}

void ObjectMode::mousePressEvent(QMouseEvent *ap, double Scale)
{
//    qDebug() << "Mouse Down " << ap->x();
    Parent->GetDataFigures()->select_figure(ap->pos() - Center, Scale);
}

void ObjectMode::mouseMoveEvent(QMouseEvent *ap)
{
//    qDebug() << "Mouse Move" << ap->x();
}

void ObjectMode::mouseReleaseEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Release" << ap->x() << " " << Center.x();
}
