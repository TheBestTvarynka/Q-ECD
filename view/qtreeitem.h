#ifndef QTREEITEM_H
#define QTREEITEM_H

#include <QTreeWidgetItem>
#include <figures/figureinterface.h>
#include <cables/iobserver.h>

class QTreeItem : public QTreeWidgetItem
{
    FigureInterface *figure;
public:
    QTreeItem(FigureInterface *new_figure,  QTreeWidgetItem *parent = nullptr) : QTreeWidgetItem(parent), figure(new_figure) {}
    QTreeItem(FigureInterface *new_figure,  QTreeWidget *parent = nullptr) : QTreeWidgetItem(parent), figure(new_figure) {}
    virtual QTreeWidgetItem *clone() const;
    FigureInterface *GetFigure() { return figure; }
};

#endif // QTREEITEM_H
