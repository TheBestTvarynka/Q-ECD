#include "drawcablemode.h"
#include "paintboard.h"
#include <QFont>

DrawCableMode::DrawCableMode(PaintBoard *parent, double scale) : ModeInterface (parent, scale)
{
    click = Qt::MouseButton::NoButton;
}

void DrawCableMode::mousePressEvent(QMouseEvent *ap)
{
    // select start point
    FigureInterface *select;
    int num_clamp = -1;
    pair<FigureInterface *, int> start = Parent->GetDataFigures()->SelectClamp(ap->pos() - Parent->GetCenter(), scale);
    select = start.first;
    num_clamp = start.second;
    if (select != nullptr && ap->button() == Qt::MouseButton::LeftButton)
    {
        click = Qt::MouseButton::LeftButton;
        Parent->setCursor(Qt::CrossCursor);
    }
    else
    {
        click = Qt::MouseButton::NoButton;
        return;
    }
    QPointF clamp = select->GetClamp(num_clamp);
    // create new cable and connect tham with figure
    Parent->GetDataCables()->AddCable(new Cable(int(clamp.x()), int(clamp.y())));
    Parent->GetDataFigures()->Register(select, num_clamp, Parent->GetDataCables()->GetLast(), 0);
    // add second point to cable
    double DeltaX = abs(double(clamp.x()) * scale - double(ap->pos().x() - Parent->GetCenter().x()));
    double DeltaY = abs(double(clamp.y()) * scale - double(ap->pos().y() - Parent->GetCenter().y()));
    if (DeltaX < DeltaY)
    {
        Parent->GetDataCables()->InsertVertex(Parent->GetDataCables()->GetLast(), clamp.x(), (ap->pos().y() - Parent->GetCenter().y()) / scale);
    }
    else
    {
        Parent->GetDataCables()->InsertVertex(Parent->GetDataCables()->GetLast(), (ap->pos().x() - Parent->GetCenter().x()) / scale, clamp.y());
    }
}

void DrawCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    if (click == Qt::MouseButton::NoButton)
        return;
    Cable *cable = Parent->GetDataCables()->GetLast();
    int points = cable->GetSize();
    pair<double, double> point = cable->GetPoint(points - 1);
    double delta = sqrt(pow(point.first * scale - ap->pos().x() + Parent->GetCenter().x(), 2) + pow(point.second * scale - ap->pos().y() + Parent->GetCenter().y(), 2));
    if (delta > scale * 2)
    {
        QPoint r_point = RoundCoordinates(point.first, point.second);
        cable->SetPoint(points - 1, r_point);
        if (cable->CheckState(points - 1, points - 2))
            cable->insert_back(r_point.x(), (ap->pos().y() - Parent->GetCenter().y()) / scale);
        else
            cable->insert_back((ap->pos().x() - Parent->GetCenter().x()) / scale, r_point.y());
    }
    else
    {
        if (cable->CheckState(points - 1, points - 2))
            point.first = (ap->pos().x() - Parent->GetCenter().x()) / scale;
        else
            point.second = (ap->pos().y() - Parent->GetCenter().y()) / scale;
        cable->SetPoint(points - 1, point.first, point.second);
    }
    cable->RemoveLoops(ap->pos() - Parent->GetCenter(), scale);
}

void DrawCableMode::mouseReleaseEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::ArrowCursor);
    if (click == Qt::MouseButton::NoButton)
    {
        return;
    }
    click = Qt::MouseButton::NoButton;

    FigureInterface *select = nullptr;      // selected figure
    int num_clamp = -1;                     // number of selecting clamp (need for register)
    QPointF clamp;                          // coordinates of selected clamp
    pair<FigureInterface *, int> finish = Parent->GetDataFigures()->SelectClamp(ap->pos() - Parent->GetCenter(), scale);
    Cable *cable = Parent->GetDataCables()->GetLast();  // current cable
    int points = cable->GetSize();
    pair<double, double> point = cable->GetPoint(points - 1);

    select = finish.first;
    num_clamp = finish.second;
    if (select != nullptr)
    {
        clamp = select->GetClamp(finish.second);
        if (cable->CheckState(points - 1, points - 2))
        {
            point.first = clamp.x();
            cable->SetPoint(points - 1, point.first, point.second);
            if (!qFuzzyCompare(clamp.y(), point.second))
            {
                cable->insert_back(clamp.x(), clamp.y());
            }
        }
        else
        {
            point.second = clamp.y();
            cable->SetPoint(points - 1, point.first, point.second);
            if (!qFuzzyCompare(clamp.x(), point.first))
                cable->insert_back(clamp.x(), clamp.y());
        }
        Parent->GetDataFigures()->Register(select, num_clamp, Parent->GetDataCables()->GetLast(), Parent->GetDataCables()->GetLast()->GetSize() - 1);
        cable->BuilData();
    }
    else
    {
        Parent->GetDataCables()->RemoveCable(cable);
    }
}
