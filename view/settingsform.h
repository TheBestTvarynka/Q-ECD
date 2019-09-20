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
#include <QTabWidget>

#include "view/style/qstylesheetstring.h"
#include "view/additionalobjects/qcolordialogwindow.h"
#include "view/settingpanels/themesettings.h"

namespace Ui {
class SettingsForm;
}

class MainGUIWindow;

class SettingsForm : public QWidget
{
    Q_OBJECT
    MainGUIWindow *Parent;
    QTabWidget *panels;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;
public:
    explicit SettingsForm(QStyleSheetString *, QStyleSheetString *, MainGUIWindow *parent);
    ~SettingsForm();
public slots:
    void ApplySettings();
    void Cancel();
    void Ok();
private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
