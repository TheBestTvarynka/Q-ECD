#include "removecablemode.h"
#include "paintboard.h"
#include <QFont>

RemoveCableMode::RemoveCableMode(PaintBoard *parent) : ModeInterface (parent)
{
    data.clear();
    color.setRgb(170, 227, 79);
    click = Qt::MouseButton::NoButton;
    selected_cables.clear();
}

void RemoveCableMode::mousePressEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::BlankCursor);
//    Parent->setCursor(Qt::CrossCursor);

    data.clear();
    QVector<QVariant> item;
    QPointF brush = QPointF(ap->pos() - Parent->GetCenter()) / Parent->GetScale();
    item.push_back(*(new QVariant(QPointF(brush))));
    item.push_back(*(new QVariant(double(Parent->GetScale() * 2))));
    data["CIRCLE"] = item;
}

void RemoveCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    QPoint brush = ap->pos() - Parent->GetCenter();
    QList<Cable *> new_selected = Parent->GetDataCables()->GetForDeleting(brush, Parent->GetScale());
    if (!shiftPressed)
    {
        Parent->GetDataCables()->SetCablesColor(new_selected, QColor(180, 220, 200));
//        selected_cables += new_selected;
        Parent->GetDataCables()->AddToSelected(new_selected);
    }
    else
    {
//        qDebug() << "remove" << new_selected.size();
        Parent->GetDataCables()->SetCablesColor(new_selected, QColor(0, 0, 0));
        Parent->GetDataCables()->RemoveFromSelected(new_selected);
    }
    data["CIRCLE"][0] = *(new QVariant(QPointF(QPointF(brush) / Parent->GetScale())));
    data["CIRCLE"][1] = *(new QVariant(double(Parent->GetScale() * 2)));
}

void RemoveCableMode::mouseReleaseEvent(QMouseEvent *)
{
//    Parent->GetDataCables()->SetSelected(selected_cables);
    Parent->setCursor(Qt::ArrowCursor);
    data.clear();
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
