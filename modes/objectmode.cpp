#include "objectmode.h"
#include "paintboard.h"

ObjectMode::ObjectMode(PaintBoard *parent) : ModeInterface (parent)
{
    click = Qt::NoButton;
    data.clear();
}

void ObjectMode::mousePressEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::SizeAllCursor);
    Parent->GetDataFigures()->select_figure(ap->pos() - Parent->GetCenter(), Parent->GetScale());
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
        Parent->GetDataFigures()->MoveSelectedFigure(Parent->GetDataFigures()->GetSelectedFigure(), (ap->x() - start_position.x()) / Parent->GetScale(), (ap->y() - start_position.y()) / Parent->GetScale());
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
