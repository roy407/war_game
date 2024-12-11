QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    city/v_capital.cpp \
    city/v_city.cpp \
    city/v_countytown.cpp \
    city/v_provincial_capital.cpp \
    city/v_town.cpp \
    field/field.cpp \
    field/v_building.cpp \
    field/v_field.cpp \
    fight.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    myscene.cpp \
    myview.cpp \
    soldier/general.cpp \
    soldier/v_heavycavalry.cpp \
    soldier/v_lightcavalry.cpp \
    soldier/v_sagittary.cpp \
    soldier/v_soldier.cpp \
    soldier/v_stonethrower.cpp \
    v_player.cpp \
    widget/attackwidget.cpp \
    widget/fieldlistdialog.cpp \
    widget/fieldwidget.cpp \
    widget/fwidget.cpp \
    widget/generalwidget.cpp \
    widget/mylistview.cpp \
    widget/mywidget.cpp \
    widget/personaldialog.cpp \
    widget/soldierdialog.cpp \
    widget/soldierlistdialog.cpp \
    widget/soldierwidget.cpp \
    widget/taskwidget.cpp \
    widget/wfwidget.cpp

HEADERS += \
    city/v_capital.h \
    city/v_city.h \
    city/v_countytown.h \
    city/v_provincial_capital.h \
    city/v_town.h \
    communicate.h \
    field/field.h \
    field/v_building.h \
    field/v_field.h \
    fight.h \
    fwidget.h \
    generalwidget.h \
    mainwindow.h \
    map.h \
    mylistview.h \
    myscene.h \
    myview.h \
    mywidget.h \
    soldier/general.h \
    soldier/v_heavycavalry.h \
    soldier/v_lightcavalry.h \
    soldier/v_sagittary.h \
    soldier/v_soldier.h \
    soldier/v_stonethrower.h \
    v_player.h \
    wfwidget.h \
    widget/attackwidget.h \
    widget/fieldlistdialog.h \
    widget/fieldwidget.h \
    widget/fwidget.h \
    widget/generalwidget.h \
    widget/mylistview.h \
    widget/mywidget.h \
    widget/personaldialog.h \
    widget/soldierdialog.h \
    widget/soldierlistdialog.h \
    widget/soldierwidget.h \
    widget/taskwidget.h \
    widget/wfwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    images.qrc
