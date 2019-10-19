#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QLabel>
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
    QString PATH;

    QMap<QString, ISetter *> colorSelectors;
public:
    explicit SettingsForm(MainGUIWindow *parent);
    QColor SelectColor(QString);
    QLayout *CreateForm();
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
