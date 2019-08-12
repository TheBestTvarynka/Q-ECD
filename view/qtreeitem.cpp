#include "qtreeitem.h"

QTreeWidgetItem *QTreeItem::clone() const
{
    // bad part of code
    // note: I need to create a copy of figure instead of get a original object
    FigureInterface *new_f = nullptr;
    *new_f = *figure;
    QTreeItem *clon = new QTreeItem(new_f, this->parent());
    return  clon;
}
