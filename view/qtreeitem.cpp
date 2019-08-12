#include "qtreeitem.h"

QTreeWidgetItem *QTreeItem::clone() const
{
    // bad part of code
    // note: I need to create a copy of figure instead of get a original object
    QTreeItem *clon = new QTreeItem(figure, this->parent());
    return  clon;
}
