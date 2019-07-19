#include "datafigures.h"

DataFigures::DataFigures()
{
//    FigureInterface *tmp = new capacitor;
//    figures.push_back(tmp);
    selected_figure = nullptr;
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
