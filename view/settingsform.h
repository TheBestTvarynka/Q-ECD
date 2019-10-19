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

#include "view/style/qstylesheetstring.h"
#include "view/additionalobjects/qcolordialogwindow.h"

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
    QMap<QString, QPushButton *> colorSelectors;
public:
    explicit SettingsForm(MainGUIWindow *parent);
    QLayout *CreateButtonParamenter(QString, QList<QWidget *>);
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
