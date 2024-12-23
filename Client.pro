QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    findopponentmenuwidget.cpp \
    findopponentwidget.cpp \
    gamefieldwidget.cpp \
    gameinfowidget.cpp \
    gameresultwidget.cpp \
    gamewidget.cpp \
    goldboxwidget.cpp \
    main.cpp \
    application.cpp \
    mainwidget.cpp \
    menuwidget.cpp \
    messagehandler.cpp \
    messagehandlerwidget.cpp \
    resultwidget.cpp \
    tcpclient.cpp

HEADERS += \
    application.h \
    findopponentmenuwidget.h \
    findopponentwidget.h \
    gamefieldwidget.h \
    gameinfowidget.h \
    gameresultwidget.h \
    gamewidget.h \
    goldboxwidget.h \
    mainwidget.h \
    menuwidget.h \
    messagehandler.h \
    messagehandlerwidget.h \
    resultwidget.h \
    tcpclient.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/images.qrc
