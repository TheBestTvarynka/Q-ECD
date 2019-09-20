#include "datafigures.h"
#include <QDebug>
#include "paintboard.h"

DataFigures::DataFigures()
{
    selected_figure = nullptr;
    selected_clamp = -1;
}

void DataFigures::add(FigureInterface *new_Figure)
{
    figures.push_back(new_Figure);
}

QList<IObserver *> DataFigures::erase(FigureInterface *select)
{
    if (select == nullptr)
        return QList<IObserver *>();
    QList<IObserver *> connected_cables = select->GetIObservers();
    select->RemoveAll();
    for (int i = 0; i < figures.size(); i++)
    {
        if (figures[i] == select)
        {
            select->DeleteTreeItem();
            delete select;
            figures.erase(figures.begin() + i);
            break;
        }
    }
    return connected_cables;
}

void DataFigures::select_figure(QPoint position, double Scale)
{
    if (selected_figure != nullptr)
        selected_figure->SetMainColor(QColor(0, 0, 255));
    if (figures.size() == 0)
    {
        selected_figure = nullptr;
        return;
    }
    double distance;
    double min_distance = sqrt(pow(position.x() - Scale * figures[0]->GetX(), 2) + pow(position.y() - Scale * figures[0]->GetY(), 2));
    selected_figure = figures[0];
    for (QVector<FigureInterface *>::iterator i = figures.begin(); i != figures.end(); ++i)
    {
        distance = sqrt(pow(position.x() - Scale * (*i)->GetX(), 2) + pow(position.y() - Scale * (*i)->GetY(), 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            selected_figure = (*i);
        }
    }
    selected_figure->SetMainColor(QColor(255, 0, 0));
}

void DataFigures::MoveSelectedFigure(FigureInterface *figure, double dX, double dY)
{
    figure->MoveFigure(dX, dY);
}

FigureInterface *DataFigures::GetSelectedFigure()
{
    return selected_figure;
}

void DataFigures::RoundCoordinates(FigureInterface *figure)
{
    double rest = figure->GetX() - int(figure->GetX());
    double newX, newY;
    if (rest >= 0.5)
        newX = int(figure->GetX()) + 1;
    else
        newX = int(figure->GetX());
    rest = figure->GetY() - int(figure->GetY());
    if (rest >= 0.5)
        newY = int(figure->GetY()) + 1;
    else
        newY = int(figure->GetY());
    figure->SetPosition(newX, newY);
}

void DataFigures::Register(FigureInterface *select, int clamp, IObserver *cable, int vertex)
{
    select->Register(cable, clamp);
    cable->AddObservable(select, vertex);
}

void DataFigures::SetSelectedFigure(FigureInterface *f)
{
    if (selected_figure != nullptr)
        selected_figure->SetMainColor(QColor(0, 0, 255));
    selected_figure = f;
    selected_figure->SetMainColor(QColor(255, 0, 0));
    emit LoadFigurePropereties(selected_figure->GetName(), selected_figure->GetValue());
}

void DataFigures::RemoveSelectedFigure()
{
    QList<IObserver *> cabs = erase(selected_figure);
    emit RemoveCables(cabs);
    emit ClearPropereties();
}

void DataFigures::SetNameSelectedFigure(const QString &name)
{
    if (selected_figure == nullptr)
        return;
    selected_figure->SetName(name);
}

void DataFigures::SetValueSelectedFigure(const QString &value)
{
    if (selected_figure == nullptr)
        return;
    selected_figure->SetValue(value);
}

void DataFigures::RotateSelectedFigureRight()
{
    if (selected_figure == nullptr)
        return;
    selected_figure->Rotate(90);
    selected_figure->Notify();
}

void DataFigures::RotateSelectedFigureLeft()
{
    if (selected_figure == nullptr)
        return;
    selected_figure->Rotate(-90);
    selected_figure->Notify();
}

pair<FigureInterface *, int> DataFigures::SelectClamp(QPoint mouse_pos, double Scale)
{
    if (figures.size() == 0)
    {
        return pair<FigureInterface *, int>(nullptr, -1.0);
    }
    pair<FigureInterface *, int> result(nullptr, -1.0);
    pair<int, double> cur;
    double min_dis = Scale * 3;
    for (int i = 0; i < figures.size(); i++)
    {
        cur = figures[i]->SelectClamp(mouse_pos, Scale);
        if (cur.first != -1 && cur.second < min_dis)
        {
            min_dis = cur.second;
            result.first = figures[i];
            result.second = cur.first;
        }
    }
    return result;
}
