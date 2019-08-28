#include "objectmode.h"
#include "paintboard.h"

ObjectMode::ObjectMode(PaintBoard *p, double s, QPoint c, int w, int h) : ModeInterface (s, p, w, h)
{
    Center = c;
    click = Qt::NoButton;
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
    Parent->setCursor(Qt::SizeAllCursor);
    Parent->GetDataFigures()->select_figure(ap->pos() - Center, scale);
    start_position = ap->pos();
    FigureInterface *sf = Parent->GetDataFigures()->GetSelectedFigure();
    if (sf != nullptr && ap->button() == Qt::LeftButton)
    {
        emit Parent->LoadFigurePropereties(sf->GetName(), sf->GetValue());
        click = ap->button();
    }
}

void ObjectMode::mouseMoveEvent(QMouseEvent *ap)
{
    if (click == Qt::LeftButton)
    {
        Parent->GetDataFigures()->MoveSelectedFigure(Parent->GetDataFigures()->GetSelectedFigure(), (ap->x() - start_position.x()) / scale, (ap->y() - start_position.y()) / scale);
        start_position = ap->pos();
    }
}

void ObjectMode::mouseReleaseEvent(QMouseEvent *)
{
    Parent->setCursor(Qt::ArrowCursor);
    if (click == Qt::LeftButton)
    {
        click = Qt::NoButton;
        Parent->GetDataFigures()->RoundCoordinates(Parent->GetDataFigures()->GetSelectedFigure());
        Parent->GetDataFigures()->GetSelectedFigure()->Notify();
    }
}
