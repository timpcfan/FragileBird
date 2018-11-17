#-------------------------------------------------
#
# Project created by QtCreator 2018-10-28T15:10:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FragileBird
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = app.ico

SOURCES += main.cpp \
    gamescene.cpp \
    gameview.cpp \
    bird.cpp \
    pipe.cpp \
    autoplayanalyzer.cpp \
    hud.cpp

HEADERS  += \
    gamescene.h \
    gameview.h \
    bird.h \
    pipe.h \
    game.h \
    game.h \
    autoplayanalyzer.h \
    hud.h

RESOURCES += \
    src.qrc


FORMS += \
    hud.ui

DISTFILES += \
    app.ico
