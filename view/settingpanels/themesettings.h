#ifndef THEMESETTINGA_H
#define THEMESETTINGA_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QColor>
#include <QPushButton>
#include <QString>

#include "view/style/qstylesheetstring.h"
#include "view/additionalobjects/qcolordialogwindow.h"

class ThemeSettings : public QWidget
{
    Q_OBJECT
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;
    QColor grid;
    QColor figure;
    QColor figure_seleced;
    QColor cable;
    QColor cable_selected;
    QString PATH;

    QWidget *colorTheme;
    QList<QWidget *> bars;
    QList<QPushButton *> buttons;
    // elements for bars
    QSpinBox *bar_border_size;
    QPushButton *bar_border_color;
    QSpinBox *bar_border_radius;
    QPushButton *bar_background;
    // elements for buttons
    QSpinBox *button_border_size;
    QPushButton *button_border_color;
    QSpinBox *button_border_radius;
    QPushButton *button_background;
    QPushButton *button_hover_color;
    QPushButton *button_text_color;
    // elements for grid settings
    QPushButton *button_grid;
    QPushButton *button_figure;
    QPushButton *button_figure_seleced;
    QPushButton *button_cable;
    QPushButton *button_cable_selected;
public:
    ThemeSettings(QString);
    QWidget *SetBarSettings();
    QWidget *SetButtonSettings();
    QWidget *SetBorderSettings();
    ~ThemeSettings();
public slots:
    void WriteSettings();

    void ClikedBarBorderColor();
    void ClikedBarBackgroundColor();
    void ChangedBarBorderSize(int);
    void ChangedBarBorderRadius(int);

    void ClikedButtonBorderColor();
    void ClikedButtonBackgroundColor();
    void ClikedButtonHoverBackgroundColor();
    void ClikedButtonTextColor();
    void ChangedButtonBorderSize(int);
    void ChangedButtonBorderRadius(int);

    void ClikedButtonFigureColor();
    void ClikedButtonFigureSelectedColor();
    void ClikedButtonCableColor();
    void ClikedButtonCableSelectedColor();
    void ClikedButtonGridColor();
};

#endif // THEMESETTINGA_H
