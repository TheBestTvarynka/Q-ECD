#include "qtree.h"
#include <QDebug>

QTree::QTree(QWidget *parent) : QTreeWidget(parent)
{
    QTreeWidgetItem *header = new QTreeWidgetItem;
    header->setText(0, "name");
    header->setText(1, "value");
    this->setHeaderItem(header);
    this->setColumnCount(2);
    this->setSortingEnabled(true);

    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(CurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
}

void QTree::CteateFigureItem(FigureInterface *new_figure)
{
    QTreeItem *new_item = new QTreeItem(new_figure, this);
    new_item->setText(0, new_figure->GetName());
    new_item->setText(1, new_figure->GetValue());
    new_figure->SetTreeItem(new_item);
    emit SetCurrentFigure(new_figure);
}

void QTree::CurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{
    qDebug() << current->text(0);
//    ((QTreeItem*)current)->GetFigure();
    emit SetCurrentFigure(((QTreeItem*)current)->GetFigure());
}
