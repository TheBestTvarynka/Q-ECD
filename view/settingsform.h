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
    // elements for bars
    QPushButton *borderColorBar;
    QPushButton *backgroundColorBar;
    QSpinBox *borderSizeBar;
    QSpinBox *borderRadiusBar;
    // elements for buttons
public:
    explicit SettingsForm(QStyleSheetString *, QStyleSheetString *, MainGUIWindow *parent);
    ~SettingsForm();
public slots:
    void ApplySettings();
    void ClikedBarBorderColor();
    void ClikedBarBackgroundColor();
    void ChangedBarBorderSize(int);
    void ChangedBarBorderRadius(int);
//    void ClikedBarBackgroundColor();
private:
    Ui::SettingsForm *ui;
signals:
    void UpdateStyle(QString, QString);
};

#endif // SETTINGSFORM_H
