QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/addlinethread.cpp \
    src/digitsvalidator.cpp \
    src/findthread.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/maprectangle.cpp \
    src/mymessagebox.cpp \
    src/myscene.cpp \
    src/myview.cpp

HEADERS += \
    inc/addlinethread.h \
    inc/digitsvalidator.h \
    inc/findthread.h \
    inc/mainwindow.h \
    inc/maprectangle.h \
    inc/mymessagebox.h \
    inc/myscene.h \
    inc/myview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
