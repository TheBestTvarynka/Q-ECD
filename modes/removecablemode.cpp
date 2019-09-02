#include "removecablemode.h"
#include "paintboard.h"
#include <QFont>

RemoveCableMode::RemoveCableMode(PaintBoard *parent, double scale) : ModeInterface (parent, scale)
{
    data.clear();
    click = Qt::MouseButton::NoButton;
    line.first = QPoint(0, 0);
    line.second = line.first;
    selected_cables.clear();
    brush = QPoint(0, 0);
    radius = 0;
}

void RemoveCableMode::mousePressEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::BlankCursor);
//    Parent->setCursor(Qt::CrossCursor);
    brush = ap->pos();
    radius = 2 * scale;
}

void RemoveCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    brush = ap->pos() - Parent->GetCenter();
    QList<Cable *> new_selected = Parent->GetDataCables()->GetForDeleting(brush, scale);
    if (!shiftPressed)
    {
        Parent->GetDataCables()->SetCablesColor(new_selected, QColor(180, 220, 200));
//        selected_cables += new_selected;
        Parent->GetDataCables()->AddToSelected(new_selected);
    }
    else
    {
        qDebug() << "remove" << new_selected.size();
        Parent->GetDataCables()->SetCablesColor(new_selected, QColor(0, 0, 0));
        Parent->GetDataCables()->RemoveFromSelected(new_selected);
    }
}

void RemoveCableMode::mouseReleaseEvent(QMouseEvent *)
{
//    Parent->GetDataCables()->SetSelected(selected_cables);
    Parent->setCursor(Qt::ArrowCursor);
    radius = 0;
}

void RemoveCableMode::keyPressEvent(QKeyEvent *event)
{
//    shiftPressed = true;
    if (event->key() == 16777248)
    {
        qDebug() << "event->key()";
        shiftPressed = true;
    }
}

void RemoveCableMode::keyReleaseEvent(QKeyEvent *)
{
    shiftPressed = false;
}
