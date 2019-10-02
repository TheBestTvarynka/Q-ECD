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
#include <QDialog>

#include "view/style/qstylesheetstring.h"
#include "view/additionalobjects/qcolordialogwindow.h"
#include "view/settingpanels/themesettings.h"
#include "view/settingpanels/listfiguressettings.h"

namespace Ui {
class SettingsForm;
}

class MainGUIWindow;

class SettingsForm : public QDialog
{
    Q_OBJECT
    MainGUIWindow *Parent;
    QTabWidget *panels;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;
public:
    explicit SettingsForm(MainGUIWindow *parent);
    ~SettingsForm();
public slots:
    void ApplySettings();
    void Cancel();
    void Ok();
private:
    Ui::SettingsForm *ui;
signals:
    void ReadSettings();
};

#endif // SETTINGSFORM_H
