/********************************************************************************
** Form generated from reading UI file 'mainguiwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGUIWINDOW_H
#define UI_MAINGUIWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGUIWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainGUIWindow)
    {
        if (MainGUIWindow->objectName().isEmpty())
            MainGUIWindow->setObjectName(QString::fromUtf8("MainGUIWindow"));
        MainGUIWindow->resize(661, 461);
        centralWidget = new QWidget(MainGUIWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainGUIWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainGUIWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 661, 25));
        MainGUIWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainGUIWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainGUIWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainGUIWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainGUIWindow->setStatusBar(statusBar);

        retranslateUi(MainGUIWindow);

        QMetaObject::connectSlotsByName(MainGUIWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainGUIWindow)
    {
        MainGUIWindow->setWindowTitle(QApplication::translate("MainGUIWindow", "Q-ECD [no file]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGUIWindow: public Ui_MainGUIWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGUIWINDOW_H
