#include "drawcablemode.h"
#include "paintboard.h"

DrawCableMode::DrawCableMode(PaintBoard *p, double s, QPoint c, int w, int h) : ModeInterface (s, p, w, h)
{
    Center = c;
    click = Qt::MouseButton::NoButton;
}

void DrawCableMode::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DrawCableMode::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);

    Weight = w;
    Height = h;
}

void DrawCableMode::paintGL(QPoint &Delta)
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

    glColor3d(1.0, 1.0, 0.0);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(scale / 10));
    glBegin(GL_POINTS);

    int nV = int(Weight / scale) + 1;
    int nH = int(Height / scale) + 1;
//    qDebug() << Center.x() << " " << Center.y();
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
    Parent->GetDataFigures()->print(scale);
}

void DrawCableMode::mousePressEvent(QMouseEvent *ap)
{
    // select start point
    FigureInterface *select;
    int clamp = -1;
    pair<QPoint, double> start = Parent->GetDataFigures()->SelectClamp(ap->pos() - Center, scale, select, clamp);
    qDebug() << "select_clamp method finished success..." << select->GetX();
    if (start.second > 0 && start.second <= scale  * 2 && ap->button() == Qt::MouseButton::LeftButton)
    {
        click = Qt::MouseButton::LeftButton;
    }
    else
    {
        click = Qt::MouseButton::NoButton;
        return;
    }
    // create new cable and connect tham with figure
    Parent->GetDataCables()->AddCable(new Cable(start.first.x(), start.first.y()));
    Parent->GetDataFigures()->Register(select, clamp, Parent->GetDataCables()->GetLast(), 0);
    // add second point to cable
    double DeltaX = abs(double(start.first.x()) * scale - double(ap->pos().x() - Center.x()));
    double DeltaY = abs(double(start.first.y()) * scale - double(ap->pos().y() - Center.y()));
    if (DeltaX < DeltaY)
    {
        Parent->GetDataCables()->InsertVertex(Parent->GetDataCables()->GetLast(), start.first.x(), (ap->pos().y() - Center.y()) / scale);
    }
    else
    {
        Parent->GetDataCables()->InsertVertex(Parent->GetDataCables()->GetLast(), (ap->pos().x() - Center.x()) / scale, start.first.y());
    }
}

void DrawCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    if (click == Qt::MouseButton::NoButton)
    {
        return;
    }
    pair<double, double> *point = Parent->GetDataCables()->GetLastPoint(Parent->GetDataCables()->GetLast());
    double delta = sqrt(pow(point->first * scale - ap->pos().x() + Center.x(), 2) + pow(point->second* scale - ap->pos().y() + Center.y(), 2));
    if (delta > scale)
    {
        QPoint r_point = RoundCoordinates(point->first, point->second);
        point->first = r_point.x();
        point->second = r_point.y();
        if (Parent->GetDataCables()->GetDirectionEnd(Parent->GetDataCables()->GetLast()))
        {
            Parent->GetDataCables()->GetLast()->insert_back(r_point.x(), (ap->pos().y() - Center.y()) / scale);
        }
        else
        {
            Parent->GetDataCables()->GetLast()->insert_back((ap->pos().x() - Center.x()) / scale, r_point.y());
        }
    }
    else
    {
        if (Parent->GetDataCables()->GetDirectionEnd(Parent->GetDataCables()->GetLast()))
            point->first = (ap->pos().x() - Center.x()) / scale;
        else
            point->second = (ap->pos().y() - Center.y()) / scale;
    }
    Parent->GetDataCables()->RemoveLoop(Parent->GetDataCables()->GetLast(), ap->pos() - Center, scale);
}

void DrawCableMode::mouseReleaseEvent(QMouseEvent *ap)
{
    if (click == Qt::MouseButton::NoButton)
    {
        return;
    }
//    click = Qt::MouseButton::NoButton;
//    pair<QPoint, double> finish = Parent->GetDataFigures()->SelectClamp(ap->pos() - Center, scale);
//    pair<double, double> *point = Parent->GetDataCables()->GetLastPoint(Parent->GetDataCables()->GetLast());
//    if (finish.second > 0 && finish.second <= scale * 2)
//    {
//        qDebug() << "connect end of cable with clamp";
//        if (Parent->GetDataCables()->GetDirectionEnd(Parent->GetDataCables()->GetLast()))
//        {
//            point->first = finish.first.x();
//            Parent->GetDataCables()->GetLast()->insert_back(finish.first.x(), finish.first.y());
//        }
//        else
//        {
//            point->first = finish.first.y();
//            Parent->GetDataCables()->GetLast()->insert_back(finish.first.x(), finish.first.y());
//        }
//    }
//    else
//    {
//        QPoint r_point = RoundCoordinates(point->first, point->second);
//        point->first = r_point.x();
//        point->second = r_point.y();
//    }
}
