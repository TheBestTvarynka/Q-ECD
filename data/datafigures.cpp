#include "datafigures.h"
#include <QDebug>

DataFigures::DataFigures()
{
//    FigureInterface *tmp = new capacitor;
//    figures.push_back(tmp);
    selected_figure = nullptr;
    selected_clamp = -1;
}

void DataFigures::print(double Scale)
{
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->print(Scale);
    }
}

void DataFigures::add(FigureInterface *new_Figure)
{
    figures.push_back(new_Figure);
}

void DataFigures::select_figure(QPoint position, double Scale)
{
    if (selected_figure != nullptr)
        selected_figure->SetMainColor(new double[3]{0.0, 1.1, 0.0});
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
    selected_figure->SetMainColor(new double[3]{1.0, 0.0, 0.0});
}

void DataFigures::MoveSelectedFigure(FigureInterface *figure, double dX, double dY)
{
    figure->MoveFigure(dX, dY);
}

FigureInterface *DataFigures::GetSelectedFigure()
{
//    if (selected_figure == nullptr)
//        return  nullptr;
    return selected_figure;
}

void DataFigures::RoundCoordinates(FigureInterface *figure)
{
    double rest = figure->GetX() - int(figure->GetX());
    double newX, newY;
    if (rest >= 0/5)
        newX = int(figure->GetX()) + 1;
    else
        newX = int(figure->GetX());
    rest = figure->GetY() - int(figure->GetY());
    if (rest >= 0/5)
        newY = int(figure->GetY()) + 1;
    else
        newY = int(figure->GetY());
    figure->SetPosition(newX, newY);
}

void DataFigures::Register(Cable *new_Cable, int vertex)
{
    if (selected_figure == nullptr || new_Cable == nullptr || selected_clamp == -1)
        return;
    selected_figure->Register(new_Cable, vertex, selected_clamp);
}

pair<QPoint, double> DataFigures::SelectClamp(QPoint mouse_pos, double Scale)
{
    if (figures.size() == 0)
    {
        return pair<QPoint, double>(QPoint(0, 0), -1);
    }
    pair<int, double> clamp, best_clamp = figures[0]->SelectClamp(mouse_pos, Scale, figures[0]->GetClams());
    for (int i = 1; i < figures.size(); i++)
    {
        clamp = figures[i]->SelectClamp(mouse_pos, Scale, figures[i]->GetClams());
        if (clamp.second < best_clamp.second && clamp.second != -1.0)
        {
            selected_figure = figures[i];
            best_clamp = clamp;
        }
    }
    selected_clamp = best_clamp.first;
    return pair<QPoint, double>(selected_figure->GetClamp(best_clamp.first), best_clamp.second);
}
