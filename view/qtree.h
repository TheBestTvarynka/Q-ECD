#ifndef QTREE_H
#define QTREE_H

#include <QTreeWidget>
#include "view/qtreeitem.h"

class QTree : public QTreeWidget
{
    Q_OBJECT
    QTreeWidgetItem *figures, *cables;
public:
    QTree(QWidget *parent = nullptr);
public slots:
    void CteateFigureItem(FigureInterface *);
    void CurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);
signals:
    void SetCurrentFigure(FigureInterface *);
};

#endif // QTREE_H
