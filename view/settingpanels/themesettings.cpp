#include "themesettings.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ThemeSettings::ThemeSettings(QString path)
{
    path = "/home/qkation/.config/q-ecd/theme/";
    PATH = path;

    QFile bar_css(path + "barStyle.css");
    bar_css.open(QFile::ReadOnly);
    if (!bar_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    barStyle = new QStyleSheetString("QWidget");
    barStyle->SetStyleSheet(QLatin1String(bar_css.readAll()));
    bar_css.close();

    QFile button_css(path + "buttonStyle.css");
    button_css.open(QFile::ReadOnly);
    buttonStyle = new QStyleSheetString("QPushButton");
    buttonStyle->SetStyleSheet(QLatin1String(button_css.readAll()));
    button_css.close();

    QFile paintboard_theme(path + "paintboard.json");
    paintboard_theme.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data_grid = paintboard_theme.readAll();
    QJsonDocument grid_json = QJsonDocument::fromJson(data_grid.toUtf8());
    paintboard_theme.close();

    figure.setNamedColor(grid_json["figure"].toString());
    figure_seleced.setNamedColor(grid_json["figure_seleced"].toString());
    cable.setNamedColor(grid_json["cable"].toString());
    cable_selected.setNamedColor(grid_json["cable_seleced"].toString());
    grid.setNamedColor(grid_json["grid"].toString());

    QVBoxLayout *page = new QVBoxLayout;
    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    page->addWidget(SetBarSettings());
    page->addWidget(SetButtonSettings());
    page->addWidget(SetBorderSettings());
    page->addItem(space);

    this->setLayout(page);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");

    connect(this, SIGNAL(windowTitleChanged(QString)), this, SLOT(WriteSettings()));
}

QWidget *ThemeSettings::SetBarSettings()
{
    QLabel *titleBar = new QLabel("Bars");
    titleBar->setStyleSheet("QLabel {"
                            "background: transparent;"
                            "color: black;"
                            "border: none; }");
    QList<QString> curBorder = barStyle->GetBorder();

    QLabel *bar_border_label = new QLabel("Border:");
    bar_border_label->setStyleSheet("QLabel {"
                                    "background: transparent;"
                                    "color: black;"
                                    "border: none; }");
    bar_border_size = new QSpinBox;
    bar_border_size->setMinimum(0);
    bar_border_size->setSingleStep(1);
    bar_border_size->setValue(curBorder[0].toInt());

    bar_border_color = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    bar_border_color->setStyleSheet(plainButton.GetStyleSheet());

    bar_border_radius = new QSpinBox;
    bar_border_radius->setMinimum(0);
    bar_border_radius->setSingleStep(1);
    bar_border_radius->setValue(curBorder[2].toInt());

    QLabel *bar_backgroud_label = new QLabel("Background:");
    bar_backgroud_label->setStyleSheet("QLabel {"
                                 "background: transparent;"
                                 "color: black;"
                                 "border: none; }");
    bar_background = new QPushButton("");
    plainButton.SetBackground(barStyle->GetBackground());
    bar_background->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *bar_border_layout = new QHBoxLayout;
    QSpacerItem *bar_border_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    bar_border_layout->addWidget(bar_border_label);
    bar_border_layout->addWidget(bar_border_size);
    bar_border_layout->addWidget(bar_border_color);
    bar_border_layout->addWidget(bar_border_radius);
    bar_border_layout->addItem(bar_border_space);
    bar_border_layout->setSpacing(15);
    QHBoxLayout *bar_background_layout = new QHBoxLayout;
    bar_background_layout->setSpacing(15);
    QSpacerItem *bar_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    bar_background_layout->addWidget(bar_backgroud_label);
    bar_background_layout->addWidget(bar_background);
    bar_background_layout->addItem(bar_background_space);

    QVBoxLayout *bar_settings = new QVBoxLayout;
    bar_settings->addWidget(titleBar);
    bar_settings->addItem(bar_border_layout);
    bar_settings->addItem(bar_background_layout);
    QWidget *bar = new QWidget;
    bars.append(bar);
    bar->setLayout(bar_settings);
    bar->setStyleSheet(barStyle->GetStyleSheet());

    connect(bar_border_color, SIGNAL(clicked()), this, SLOT(ClikedBarBorderColor()));
    connect(bar_border_size, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderSize(int)));
    connect(bar_border_radius, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderRadius(int)));
    connect(bar_background, SIGNAL(clicked()), this, SLOT(ClikedBarBackgroundColor()));

    return bar;
}

QWidget *ThemeSettings::SetButtonSettings()
{
    QLabel *titleBar = new QLabel("Buttons");
    titleBar->setStyleSheet("QLabel {"
                            "background: transparent;"
                            "color: black;"
                            "border: none; }");
    QList<QString> curBorder = buttonStyle->GetBorder();

    QLabel *button_border_label = new QLabel("Border:");
    button_border_label->setStyleSheet("QLabel {"
                                       "background: transparent;"
                                       "color: black;"
                                       "border: none; }");
    button_border_size = new QSpinBox;
    button_border_size->setMinimum(0);
    button_border_size->setSingleStep(1);
    button_border_size->setValue(curBorder[0].toInt());

    button_border_color = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    button_border_color->setStyleSheet(plainButton.GetStyleSheet());

    button_border_radius = new QSpinBox;
    button_border_radius->setMinimum(0);
    button_border_radius->setSingleStep(1);
    button_border_radius->setValue(curBorder[2].toInt());

    QLabel *button_backgroud_label = new QLabel("Background:");
    button_backgroud_label->setStyleSheet("QLabel {"
                                          "background: transparent;"
                                          "color: black;"
                                          "border: none; }");
    button_background = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetBackground());
    button_background->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *button_hover_label = new QLabel("Hover:");
    button_hover_label->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_hover_color = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetHoverBackground());
    button_hover_color->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *button_text_color_label = new QLabel("Text color:");
    button_text_color_label->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_text_color = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetTextColor());
    button_text_color->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *button_border_layout = new QHBoxLayout;
    button_border_layout->setSpacing(15);
    QSpacerItem *button_border_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_border_layout->addWidget(button_border_label);
    button_border_layout->addWidget(button_border_size);
    button_border_layout->addWidget(button_border_color);
    button_border_layout->addWidget(button_border_radius);
    button_border_layout->addItem(button_border_space);

    QHBoxLayout *button_background_layout = new QHBoxLayout;
    button_background_layout->setSpacing(15);
    QSpacerItem *button_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_background_layout->addWidget(button_backgroud_label);
    button_background_layout->addWidget(button_background);
    button_background_layout->addItem(button_background_space);

    QHBoxLayout *button_hover_layout = new QHBoxLayout;
    button_hover_layout->setSpacing(15);
    QSpacerItem *button_hover_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_hover_layout->addWidget(button_hover_label);
    button_hover_layout->addWidget(button_hover_color);
    button_hover_layout->addItem(button_hover_background_space);

    QHBoxLayout *button_text_color_layout = new QHBoxLayout;
    button_text_color_layout->setSpacing(15);
    QSpacerItem *button_text_color_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_text_color_layout->addWidget(button_text_color_label);
    button_text_color_layout->addWidget(button_text_color);
    button_text_color_layout->addItem(button_text_color_space);

    QVBoxLayout *button_settings = new QVBoxLayout;
    button_settings->addWidget(titleBar);
    button_settings->addItem(button_border_layout);
    button_settings->addItem(button_background_layout);
    button_settings->addItem(button_hover_layout);
    button_settings->addItem(button_text_color_layout);
    QWidget *button = new QWidget;
    bars.append(button);
    button->setLayout(button_settings);
    button->setStyleSheet(barStyle->GetStyleSheet());

    connect(button_border_color, SIGNAL(clicked()), this, SLOT(ClikedButtonBorderColor()));
    connect(button_border_size, SIGNAL(valueChanged(int)), this, SLOT(ChangedButtonBorderSize(int)));
    connect(button_border_radius, SIGNAL(valueChanged(int)), this, SLOT(ChangedButtonBorderRadius(int)));
    connect(button_background, SIGNAL(clicked()), this, SLOT(ClikedButtonBackgroundColor()));
    connect(button_hover_color, SIGNAL(clicked()), this, SLOT(ClikedButtonHoverBackgroundColor()));
    connect(button_text_color, SIGNAL(clicked()), this, SLOT(ClikedButtonTextColor()));
    return button;
}

QWidget *ThemeSettings::SetBorderSettings()
{
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
//    plainButton.SetBackground(figure.name());
    plainButton.SetBackground("#ff00aa");
    plainButton.EraseBlock("QPushButton::hover");

    QLabel *figure_color_lable = new QLabel("Figure color");
    figure_color_lable->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_figure = new QPushButton("");
    plainButton.SetBackground(figure.name());
    button_figure->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *figure_selected_color_lable = new QLabel("Selected figure color");
    figure_selected_color_lable->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_figure_seleced = new QPushButton("");
    plainButton.SetBackground(figure_seleced.name());
    button_figure_seleced->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *cable_color_lable = new QLabel("Cable color");
    cable_color_lable->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_cable = new QPushButton("");
    plainButton.SetBackground(cable.name());
    button_cable->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *cable_selected_color_lable = new QLabel("Selected figure color");
    cable_selected_color_lable->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_cable_selected = new QPushButton("");
    plainButton.SetBackground(cable_selected.name());
    button_cable_selected->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *grid_color_lable = new QLabel("Grid color");
    grid_color_lable->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_grid = new QPushButton("");
    plainButton.SetBackground(grid.name());
    button_grid->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *figure_layout = new QHBoxLayout;
    figure_layout->setSpacing(15);
    figure_layout->addWidget(figure_color_lable);
    figure_layout->addWidget(button_figure);
    figure_layout->addWidget(figure_selected_color_lable);
    figure_layout->addWidget(button_figure_seleced);

    QHBoxLayout *cable_layout = new QHBoxLayout;
    cable_layout->setSpacing(15);
    cable_layout->addWidget(cable_color_lable);
    cable_layout->addWidget(button_cable);
    cable_layout->addWidget(cable_selected_color_lable);
    cable_layout->addWidget(button_cable_selected);

    QHBoxLayout *grid_layot = new QHBoxLayout;
    grid_layot->setSpacing(15);
    grid_layot->addWidget(grid_color_lable);
    grid_layot->addWidget(button_grid);

    QLabel *bar_name = new QLabel("Board");
    bar_name->setStyleSheet("QLabel {"
                            "background: transparent;"
                            "color: black;"
                            "border: none; }");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bar_name);
    layout->addItem(figure_layout);
    layout->addItem(cable_layout);
    layout->addItem(grid_layot);

    QWidget *board_settings = new QWidget;
    board_settings->setStyleSheet(barStyle->GetStyleSheet());
    board_settings->setLayout(layout);
    bars.append(board_settings);

    return board_settings;
}

void ThemeSettings::WriteSettings()
{
    QFile bar_css(PATH + "barStyle.css");
    bar_css.open(QFile::WriteOnly);
    if (!bar_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    bar_css.write(barStyle->GetStyleSheet().toUtf8());
    bar_css.close();

    QFile button_css(PATH + "buttonStyle.css");
    button_css.open(QFile::WriteOnly);
    if (!button_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    button_css.write(buttonStyle->GetStyleSheet().toUtf8());
    button_css.close();

    QJsonObject grid_json;
    grid_json["figure"] = figure.name();
    grid_json["figure_seleced"] = figure_seleced.name();
    grid_json["cable"] = cable.name();
    grid_json["cable_seleced"] = cable_selected.name();
    grid_json["grid"] = grid.name();

    QFile paintboard_theme(PATH + "paintboard1.json");
    paintboard_theme.open(QFile::WriteOnly);
    if (!paintboard_theme.isOpen())
    {
        qDebug() << "error: file not found";
    }
    paintboard_theme.write(QJsonDocument(grid_json).toJson(QJsonDocument::Indented));
    paintboard_theme.close();
}

ThemeSettings::~ThemeSettings()
{

}

void ThemeSettings::ClikedBarBorderColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(bar_border_color->styleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor barColor = color->GetColor();
    delete color;
    if (!barColor.isValid())
        return;
    str.SetBackground(barColor.name());
    bar_border_color->setStyleSheet(str.GetStyleSheet());

    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(border[0], barColor.name(), border[2]);
}

void ThemeSettings::ClikedBarBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(barStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor barColor = color->GetColor();
    delete color;
    if (!barColor.isValid())
        return;
    barStyle->SetBackground(barColor.name());
    str.SetStyleSheet(bar_background->styleSheet());
    str.SetBackground(barColor.name());
    bar_background->setStyleSheet(str.GetStyleSheet());
}

void ThemeSettings::ChangedBarBorderSize(int size)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(QString::number(size), border[1], border[2]);
}

void ThemeSettings::ChangedBarBorderRadius(int radius)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(border[0], border[1], QString::number(radius));
}

void ThemeSettings::ClikedButtonBorderColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(button_border_color->styleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    str.SetBackground(buttonColor.name());
    button_border_color->setStyleSheet(str.GetStyleSheet());

    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(border[0], buttonColor.name(), border[2]);
}

void ThemeSettings::ClikedButtonBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetBackground(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_background->setStyleSheet(str.GetStyleSheet());
}

void ThemeSettings::ClikedButtonHoverBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetHoverBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetHoverBackground(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_hover_color->setStyleSheet(str.GetStyleSheet());
}

void ThemeSettings::ClikedButtonTextColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetTextColor());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetTextColor(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_text_color->setStyleSheet(str.GetStyleSheet());
}

void ThemeSettings::ChangedButtonBorderSize(int size)
{
    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(QString::number(size), border[1], border[2]);
}

void ThemeSettings::ChangedButtonBorderRadius(int radius)
{
    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(border[0], border[1], QString::number(radius));
}
