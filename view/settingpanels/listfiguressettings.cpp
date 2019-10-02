#include "listfiguressettings.h"

ListFiguresSettings::ListFiguresSettings(QString path)
{
    PATH = path;

    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground("#ff00ff");
    plainButton.EraseBlock("QPushButton::hover");

    QLabel *background = new QLabel("Background");
    button_background = new QPushButton("");
    button_background->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *background_layot = new QHBoxLayout;
    background_layot->addWidget(background);
    background_layot->addWidget(button_background);

    QLabel *text_color = new QLabel("Text color");
    button_text_color = new QPushButton("");
    button_text_color->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *text_color_layot = new QHBoxLayout;
    text_color_layot->addWidget(text_color);
    text_color_layot->addWidget(button_text_color);

    QLabel *selection_background = new QLabel("selection background");
    button_selection = new QPushButton("");
    button_selection->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *selection_layot = new QHBoxLayout;
    selection_layot->addWidget(selection_background);
    selection_layot->addWidget(button_selection);

    QLabel *item_label = new QLabel("Item background color:");
    item_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QLabel *alternate = new QLabel("alternate");
    button_item_alternate = new QPushButton("");
    button_item_alternate->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *alternate_layot = new QHBoxLayout;
    alternate_layot->addWidget(alternate);
    alternate_layot->addWidget(button_item_alternate);

    QLabel *selected_color = new QLabel("item selected coloe");
    button_item_selected = new QPushButton("");
    button_item_selected->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *selected_layot = new QHBoxLayout;
    selected_layot->addWidget(selected_color);
    selected_layot->addWidget(button_item_selected);

    QLabel *selected_active_color = new QLabel("selected active color");
    button_item_selected_active = new QPushButton("");
    button_item_selected_active->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *item_selected_active_layot = new QHBoxLayout;
    item_selected_active_layot->addWidget(selected_active_color);
    item_selected_active_layot->addWidget(button_item_selected_active);

    QLabel *selected_not_active_color = new QLabel("selected not active color");
    button_item_selected_non_active = new QPushButton("");
    button_item_selected_non_active->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *item_non_selected_layot = new QHBoxLayout;
    item_non_selected_layot->addWidget(selected_not_active_color);
    item_non_selected_layot->addWidget(button_item_selected_non_active);

    QLabel *hover_color = new QLabel("hover");
    button_item_hover = new QPushButton("");
    button_item_hover->setStyleSheet(plainButton.GetStyleSheet());
    QHBoxLayout *hover_layot = new QHBoxLayout;
    hover_layot->addWidget(hover_color);
    hover_layot->addWidget(button_item_hover);

    QVBoxLayout *all = new QVBoxLayout;
    all->addItem(background_layot);
    all->addItem(text_color_layot);
    all->addItem(selection_layot);
    all->addWidget(item_label);
    all->addItem(alternate_layot);
    all->addItem(selected_layot);
    all->addItem(item_selected_active_layot);
    all->addItem(item_non_selected_layot);
    all->addItem(hover_layot);
    QSpacerItem *result_space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Expanding);
    all->addItem(result_space);

    this->setLayout(all);
}
