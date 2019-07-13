#include "datafigures.h"

DataFigures::DataFigures()
{

}

void DataFigures::print()
{
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->print();
    }
}
