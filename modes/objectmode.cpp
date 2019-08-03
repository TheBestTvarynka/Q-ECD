#include "objectmode.h"
#include "paintboard.h"

ObjectMode::ObjectMode(PaintBoard *p, double s, QPoint c, int w, int h) : ModeInterface (s, p, w, h) { Center = c;}

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
void ObjectMode::paintGL(QPoint &Delta)
{
    QColor background(220, 220, 220, 255);
    //    qglClearColor(background);
    glClearColor(220, 220, 220, 255);
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

    glColor3d(0.0, 0.0, 1.0);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(scale / 10));
    glBegin(GL_POINTS);

    int nV = int(Weight / scale) + 1;
    int nH = int(Height / scale) + 1;
    double DeltaX = Center.x() - int(Center.x() / scale) * scale, DeltaY = Center.y() - int(Center.y() / scale) * scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * scale - Center.x() + DeltaX), float(i * scale - Center.y() + DeltaY));
        }
    }
    glEnd();

    Parent->GetDataCables()->print(scale);
    Parent->GetDataFigures()->print(scale, Parent);
}

void ObjectMode::mousePressEvent(QMouseEvent *ap)
{
//    qDebug() << "Mouse Down " << ap->x();
    Parent->GetDataFigures()->select_figure(ap->pos() - Center, scale);
    start_position = ap->pos();
}

void ObjectMode::mouseMoveEvent(QMouseEvent *ap)
{
//    qDebug() << "Mouse Move" << ap->x();
    Parent->GetDataFigures()->MoveSelectedFigure(Parent->GetDataFigures()->GetSelectedFigure(), (ap->x() - start_position.x()) / scale, (ap->y() - start_position.y()) / scale);
    start_position = ap->pos();
}

void ObjectMode::mouseReleaseEvent(QMouseEvent *ap)
{
//    qDebug() << "Mouse Release" << ap->x() << " " << Center.x();
    Parent->GetDataFigures()->RoundCoordinates(Parent->GetDataFigures()->GetSelectedFigure());
    Parent->GetDataFigures()->GetSelectedFigure()->Notify();
}
