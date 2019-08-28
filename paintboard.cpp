#include "paintboard.h"
#include <QDebug>

PaintBoard::PaintBoard(QWidget *parent, ModeInterface *start_state): QGLWidget(parent)
{
    Scale = 20;
    Delta.setX(0);
    Delta.setY(0);
    Center = Delta;
    click = Qt::MouseButton::NoButton;

    paint_devices.insert("GL_LINE_LOOP", &PaintBoard::LINE_LOOP);
    paint_devices.insert("GL_LINES", &PaintBoard::LINES);
    paint_devices.insert("TEXT", &PaintBoard::TEXT);

    connect(&mpTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mpTimer.start(10);

    if (start_state == nullptr)
        mode = new ObjectMode(this, Scale, QPoint(0, 0), width(), height());
}

void PaintBoard::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PaintBoard::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);
}

void PaintBoard::paintGL()
{
//    mode->paintGL(Delta);
    QColor background(220, 220, 220, 255);
    glClearColor(220, 220, 220, 255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glTranslated(Delta.x(), Delta.y(), 0);
//    Center += Delta;

    glColor3d(0.0, 0.0, 1.0);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(Scale / 10));
    glBegin(GL_POINTS);

    int nV = int(width() / Scale) + 1;
    int nH = int(height() / Scale) + 1;
    double DeltaX = Center.x() - int(Center.x() / Scale) * Scale, DeltaY = Center.y() - int(Center.y() / Scale) * Scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * Scale - Center.x() + DeltaX), float(i * Scale - Center.y() + DeltaY));
        }
    }
    glEnd();

    QVector<FigureInterface *> f = figures.GetFigures();
    QMap<QString, QVector<QVariant> > d;
    pair<double, double> pos;
    foreach (FigureInterface *i, f)
    {
        d = i->GetData();
        pos = i->GetPos();
        glPushMatrix();
        glTranslated(pos.first * Scale, pos.second * Scale, 0);
        glRotatef(i->GetRotation(), 0.0, 0.0, 1.0);

        QMapIterator<QString, QVector<QVariant> > iT(d);
        while (iT.hasNext())
        {
            iT.next();
            (this->*paint_devices[iT.key()])(iT.value());
        }

        glPopMatrix();
    }
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
        Center += Delta;
        glTranslated(Delta.x(), Delta.y(), 0);
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

void PaintBoard::keyPressEvent(QKeyEvent *event)
{
    mode->keyPressEvent(event);
}

void PaintBoard::keyReleaseEvent(QKeyEvent *event)
{
    mode->keyReleaseEvent(event);
}

void PaintBoard::LINES(QVector<QVariant> lines)
{
//    qDebug() << "LINES";
    QPointF point;
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINES);
    foreach (QVariant i, lines)
    {
        point = i.toPointF();
        glVertex2f(float(point.x()) * float(Scale), float(point.y()) * float(Scale));
    }
    glEnd();
}

void PaintBoard::LINE_LOOP(QVector<QVariant> lines)
{
//    qDebug() << "LINE_LOOP";
    QPointF point;
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINE_LOOP);
    foreach (QVariant i, lines)
    {
        point = i.toPointF();
        glVertex2f(float(point.x()) * float(Scale), float(point.y()) * float(Scale));
    }
    glEnd();
}

void PaintBoard::TEXT(QVector<QVariant> text)
{
    if (text.size() != 3)
        return;
    QPointF f_pos = text[0].toPointF();
    QPointF pos = text[1].toPointF();
    renderText(Center.x() + int(pos.x() * Scale + f_pos.x() * Scale), Center.y() + int(pos.y() * Scale + f_pos.y() * Scale), text[2].toString(), QFont("Arial", int(Scale * 0.67), 5, false));
}

void PaintBoard::SetMode(ModeInterface *newMode)
{
    delete mode;
    mode = newMode;
}

void PaintBoard::CreateCustomFigure(int type, int x, int y, int rotation, QString name, QString value)
{
    FigureInterface *new_figure = creator.GetNewFigure(type, x, y, rotation, name, value);
    figures.add(new_figure);
    emit AddToTree(new_figure);
}

void PaintBoard::SetSelectedFigure(FigureInterface *f)
{
    figures.SetSelectedFigure(f);
    emit LoadFigurePropereties(f->GetName(), f->GetValue());
}

void PaintBoard::CreateFigure(int f)
{
    FigureInterface *new_figure = creator.GetNewFigure(f, int((width() / 2 - mode->GetCenter().x()) / Scale), int((height() / 2 - mode->GetCenter().y()) / Scale), 0, "F" + QString::number(figures.size()), "vl");
    figures.add(new_figure);
    emit AddToTree(new_figure);
}

void PaintBoard::RemoveSelectedFigure()
{
    QList<IObserver *> cabs = figures.erase(figures.GetSelectedFigure());
    cables.RemoveCables(cabs);
    emit ClearPropereties();
}

void PaintBoard::RemoveSelectedCables()
{
    cables.RemoveCables(cables.GetSelectedCables());
    cables.ClearSelected();
}

void PaintBoard::SetNameSelectedFigure(const QString &name)
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    selected->SetName(name);
}

void PaintBoard::SetValueSelectedFigure(const QString &value)
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    selected->SetValue(value);
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

void PaintBoard::CopySelectedFigure()
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    QString x; x.setNum(selected->GetX());
    QString y; y.setNum(selected->GetY());
    QString r; r.setNum(selected->GetRotation());
    QString n = selected->GetName();
    QString v = selected->GetValue();
    QString t; t.setNum(selected->GetType());
    QString buffer = x + ";" + y + ";" + r + ";" + n + ";" + v + ";" + t;
    qDebug() << buffer;
    QClipboard *buf = QApplication::clipboard();
    buf->setText(buffer);
}

void PaintBoard::PasteFromBuffer()
{
    QClipboard *buffer = QApplication::clipboard();
    QString str = buffer->text();
    if (str.isNull())
        return;
    int x =  str.section(';', 0, 0).toInt();
    int y = str.section(';', 1, 1).toInt();
    int rotation = str.section(';', 2, 2).toInt();
    QString name = str.section(';', 3, 3);
    QString value = str.section(';', 4, 4);
    int type =  str.section(';', 5, 5).toInt();
    CreateCustomFigure(type, x, y, rotation, name, value);
}

void PaintBoard::SetRemoveCableMode()
{
    ModeInterface *Mode = new RemoveCableMode(this, GetScale(), GetCenter(), width(), height());
    delete mode;
    mode = Mode;
}
