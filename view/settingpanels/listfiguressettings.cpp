#include "listfiguressettings.h"

ListFiguresSettings::ListFiguresSettings(QString path)
{
    PATH = path;
    QWidget *panel = new QWidget;
    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(panel);
    this->setLayout(main);
}
