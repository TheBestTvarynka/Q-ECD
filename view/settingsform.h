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

#include "view/additionalobjects/qcolordialogwindow.h"

namespace Ui {
class SettingsForm;
}

class MainGUIWindow;

class SettingsForm : public QWidget
{
    Q_OBJECT
    MainGUIWindow *Parent;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;

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
public:
    explicit SettingsForm(QStyleSheetString *, QStyleSheetString *, MainGUIWindow *parent);
    QWidget *SetBarSettings();
    QWidget *SetButtonSettings();
    ~SettingsForm();
public slots:
    void ApplySettings();

    void ClikedBarBorderColor();
    void ClikedBarBackgroundColor();
    void ChangedBarBorderSize(int);
    void ChangedBarBorderRadius(int);

    void ClikedButtonBorderColor();
    void ClikedButtonBackgroundColor();
    void ClikedButtonHoverBackgroundColor();
    void ChangedButtonBorderSize(int);
    void ChangedButtonBorderRadius(int);
private:
    Ui::SettingsForm *ui;
signals:
    void UpdateStyle(QString, QString);
};

#endif // SETTINGSFORM_H
