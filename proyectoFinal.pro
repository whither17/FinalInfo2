QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    code/nivel2/arma.cpp \
    code/nivel2/bala.cpp \
    code/nivel2/enemy.cpp \
    code/nivel2/item.cpp \
    code/nivel0/level0.cpp \
    code/nivel2/level2.cpp \
    code/main.cpp \
    code/mainwindow.cpp \
    code/nivel2/player.cpp \
    code/nivel1/bottle.cpp \
    code/nivel1/liquid.cpp \
    code/nivel1/pocion.cpp \
    code/nivel1/level1.cpp \
    code/nivel1/pp.cpp

HEADERS += \
    code/nivel2/arma.h \
    code/nivel2/bala.h \
    code/nivel2/enemy.h \
    code/nivel2/item.h \
    code/nivel0/level0.h \
    code/nivel2/level2.h \
    code/macros.h \
    code/mainwindow.h \
    code/nivel2/player.h \
    code/nivel1/bottle.h \
    code/nivel1/liquid.h \
    code/nivel1/pocion.h \
    code/nivel1/level1.h \
    code/nivel1/pp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc \
    reourses.qrc \
    sound.qrc
