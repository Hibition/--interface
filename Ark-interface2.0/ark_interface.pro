QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entity.cpp \
    arkinfo.cpp \
    clickedlabel.cpp \
    fao.cpp \
    interface.cpp \
    main.cpp \
    picture.cpp \
    widget.cpp

HEADERS += \
    Entity.h \
    arkinfo.h \
    clickedlabel.h \
    fao.h \
    interface.h \
    picture.h \
    widget.h

FORMS += \
    interface.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    logo.rc

RC_FILE += logo.rc
