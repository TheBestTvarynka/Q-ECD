#include "datacables.h"
#include <QDebug>

DataCables::DataCables()
{
    selected.clear();
}

void DataCables::AddCable(Cable *new_Cable)
{
    cables.push_back(new_Cable);
}

bool DataCables::RemoveCable(Cable *select)
{
    if (select == nullptr)
        return false;
    select->RemoveAllObservable();
    for (int i = 0; i < cables.size(); i++)
    {
        if (cables[i] == select)
        {
            delete select;
            cables.erase(cables.begin() + i);
            return true;
        }
    }
    return false;
}

void DataCables::RemoveCables(QList<IObserver *> c)
{
    foreach (IObserver *i, c)
    {
        RemoveCable((Cable *)(i));
    }
}

void DataCables::RemoveCables(QList<Cable *>c)
{
    foreach (Cable *i, c)
    {
        RemoveCable(i);
    }
}

void DataCables::print(double Scale)
{
    for(int i = 0; i < cables.size(); i++)
        cables[i]->print(Scale);
}

void DataCables::SetCablesColor(QList<Cable *>c, double color[3])
{
    foreach (Cable *i, c)
    {
        i->SetMainColor(color);
    }
}

void DataCables::InsertVertex(Cable *c, double x, double y)
{
    c->insert_back(x, y);
}

void DataCables::RemoveLoop(Cable *cable, QPoint pos, double scale)
{
    cable->RemoveLoops(pos, scale);
}

void DataCables::RemoveFromSelected(QList<Cable *> left)
{
    foreach (Cable *i, left)
    {
        selected.removeOne(i);
    }
}

void DataCables::AddToSelected(QList<Cable *> additional)
{
    selected.append(additional);
}

QList<Cable *> DataCables::GetForDeleting(pair<QPoint, QPoint> sections, double scale)
{
    QList<Cable *> removing;
    foreach (Cable *i, cables)
    {
        if (i->CheckIntersection(sections, scale))
            removing.append(i);
    }
    return removing;
}

QList<Cable *> DataCables::GetForDeleting(QPoint brush, double scale)
{
    QList<Cable *> removing;
    foreach (Cable *i, cables)
    {
//        if (!i->IsMarked() && i->CheckIntersection(brush, scale))
        if (i->CheckIntersection(brush, scale))
            removing.append(i);
    }
    return removing;
}

bool DataCables::GetDirectionEnd(Cable *cable)
{
    int last_point = cable->GetSize() - 1;
    if (qFuzzyCompare(cable->GetPoint(last_point).first, cable->GetPoint(last_point - 1).first))
        return false;
    else
        return true;
}
