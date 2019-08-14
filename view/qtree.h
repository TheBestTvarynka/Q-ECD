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
};

#endif // QTREE_H
