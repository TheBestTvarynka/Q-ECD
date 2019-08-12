#ifndef QTREEITEM_H
#define QTREEITEM_H

#include <QTreeWidgetItem>
#include <figures/figureinterface.h>

class QTreeItem : public QTreeWidgetItem
{
    FigureInterface *figure;
public:
    QTreeItem(FigureInterface *new_figure,  QTreeWidgetItem *parent = nullptr) : QTreeWidgetItem(parent), figure(new_figure) {}
    virtual QTreeWidgetItem *clone() const;
};

#endif // QTREEITEM_H
