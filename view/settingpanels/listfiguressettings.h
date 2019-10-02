#ifndef LISTFIGURESSETTINGS_H
#define LISTFIGURESSETTINGS_H

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


class ListFiguresSettings : public QWidget
{
    Q_OBJECT
    QString PATH;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;
    QWidget *colorTheme;
    QList<QWidget *> bars;
    QList<QPushButton *> buttons;

    QPushButton *button_background;
    QPushButton *button_text_color;
    QPushButton *button_selection;
    QSpinBox *spin_font_size;
    QPushButton *button_item_alternate;
    QPushButton *button_item_selected;
    QPushButton *button_item_selected_active;
    QPushButton *button_item_selected_non_active;
    QPushButton *button_item_hover;
public:
    ListFiguresSettings(QString);
};

#endif // LISTFIGURESSETTINGS_H
