#include "objectmode.h"
#include "paintboard.h"

ObjectMode::ObjectMode(PaintBoard *parent, double scale) : ModeInterface (parent, scale)
{
    click = Qt::NoButton;
}

void ObjectMode::mousePressEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::SizeAllCursor);
    Parent->GetDataFigures()->select_figure(ap->pos() - Parent->GetCenter(), scale);
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
