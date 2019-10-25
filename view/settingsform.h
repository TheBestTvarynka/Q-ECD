#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QList>
#include <QMap>

#include "additionalobjects/qchoosecolorbutton.h"
#include "additionalobjects/qchoosenumberbox.h"

namespace Ui {
class SettingsForm;
}

class MainGUIWindow;

class SettingsForm : public QDialog
{
    Q_OBJECT
    MainGUIWindow *Parent;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;
    QStyleSheetString *listNewStyle;
    QString PATH;
    QWidget *formSettings;
    QList<QWidget *> allBars;
    QList<QWidget *> allButtons;

    QMap<QString, ISetter *> barTheme;
    QMap<QString, ISetter *> buttonsTheme;
    QMap<QString, ISetter *> listNewTheme;
public:
    explicit SettingsForm(MainGUIWindow *parent);
    QWidget *CreateForm();
    QLayout *CreateOptionLine(QString, QWidget *);
    ~SettingsForm();
public slots:
    void LoadSettings();
    void ApplySettings();
    void Cancel();
    void Ok();
private:
    Ui::SettingsForm *ui;
signals:
    void ReadSettings();
};

#endif // SETTINGSFORM_H
