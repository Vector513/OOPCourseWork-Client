QT       += core gui
QT       += network
RESOURCES += \
    resources.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    gamefield.cpp \
    gamewindow.cpp \
    goldbox.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    opponentsearchwindow.cpp \
    tcpClient.cpp

HEADERS += \
    application.h \
    gamefield.h \
    gamewindow.h \
    goldbox.h \
    mainwindow.h \
    menu.h \
    opponentsearchwindow.h \
    tcpClient.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES +=
