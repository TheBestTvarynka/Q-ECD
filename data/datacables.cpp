#include "datacables.h"
#include <QDebug>

DataCables::DataCables()
{

}

void DataCables::AddCable(Cable *new_Cable)
{
    cables.push_back(new_Cable);
}

void DataCables::print(double Scale)
{
    for(int i = 0; i < cables.size(); i++)
        cables[i]->print(Scale);
}

void DataCables::InsertVertex(Cable *c, double x, double y)
{
    c->insert_back(x, y);
}

void DataCables::RemoveLoop(Cable *cable, QPoint pos, double scale)
{
    cable->RemoveLoops(pos, scale);
}

bool DataCables::GetDirectionEnd(Cable *cable)
{
    int last_point = cable->GetSize() - 1;
    if (cable->GetPoint(last_point).first == cable->GetPoint(last_point - 1).first)
        return false;
    else
        return true;
}