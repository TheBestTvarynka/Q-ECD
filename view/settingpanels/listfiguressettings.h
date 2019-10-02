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
public:
    ListFiguresSettings(QString);
};

#endif // LISTFIGURESSETTINGS_H
