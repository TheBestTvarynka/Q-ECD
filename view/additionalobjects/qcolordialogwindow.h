#ifndef QCOLORDIALOGWINDOW_H
#define QCOLORDIALOGWINDOW_H

#include <QDialog>

#include <QWidget>
#include <QColor>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>

class QColorDialogWindow : public QDialog
{
    Q_OBJECT
    QColor color;
    QPushButton *example;
    QSpinBox *red;
    QSpinBox *green;
    QSpinBox *blue;
public:
    QColorDialogWindow(QColor initial);
    QColor GetColor();
    ~QColorDialogWindow();
signals:
    void SetName(QString);
public slots:
    void RedChanged(int);
    void GreenChanged(int);
    void BlueChanged(int);
    void SetNameColor(QString);
    void BreakColor();
};

#endif // QCOLORDIALOGWINDOW_H
