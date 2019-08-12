#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T19:37:02
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Q-ECD
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainguiwindow.cpp \
    modes/modeinterface.cpp \
    figures/figureinterface.cpp \
    figures/iobservable.cpp \
    figures/resistor.cpp \
    data/datafigures.cpp \
    modes/objectmode.cpp \
    paintboard.cpp \
    figures/capacitor.cpp \
    cables/cable.cpp \
    modes/drawcablemode.cpp \
    cables/iobserver.cpp \
    data/datacables.cpp \
    figures/figurecreator.cpp \
    view/qtreeitem.cpp

HEADERS += \
        mainguiwindow.h \
    modes/modeinterface.h \
    figures/figureinterface.h \
    figures/iobservable.h \
    figures/resistor.h \
    data/datafigures.h \
    modes/objectmode.h \
    paintboard.h \
    figures/capacitor.h \
    cables/cable.h \
    modes/drawcablemode.h \
    cables/iobserver.h \
    data/datacables.h \
    figures/figurecreator.h \
    view/qtreeitem.h

FORMS += \
        mainguiwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
