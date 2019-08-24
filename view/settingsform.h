#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QColorDialog>
#include <QColor>
#include <QPushButton>
#include <QList>
#include "view/style/qstylesheetstring.h"

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;

    QWidget *colorTheme;
    QList<QWidget *> bars;
public:
    explicit SettingsForm(QStyleSheetString *, QStyleSheetString *, QWidget *parent = nullptr);
    ~SettingsForm();
public slots:
    void ApplySettings();
private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
