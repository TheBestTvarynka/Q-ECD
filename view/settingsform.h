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

class MainGUIWindow;

class SettingsForm : public QWidget
{
    Q_OBJECT
    MainGUIWindow *Parent;
    QStyleSheetString *barStyle;
    QStyleSheetString *buttonStyle;

    QWidget *colorTheme;
    QList<QWidget *> bars;
public:
    explicit SettingsForm(QStyleSheetString *, QStyleSheetString *, MainGUIWindow *parent);
    ~SettingsForm();
public slots:
    void ApplySettings();
private:
    Ui::SettingsForm *ui;
signals:
    void UpdateStyle(QString, QString);
};

#endif // SETTINGSFORM_H
