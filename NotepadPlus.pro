QT       += core gui
CONFIG      += qscintilla2

#设置应用程序图标
RC_ICONS =./icons/npp.ico

#设置编译的程序名
#TARGET=Notepad++

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configfile.cpp \
    languages.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp \
    pugixml/pugixml.cpp \
    tabscintilla.cpp \
    tools.cpp

HEADERS += \
    configfile.h \
    languages.h \
    mainwindow.h \
    parameters.h \
    pugixml/pugiconfig.hpp \
    pugixml/pugixml.hpp \
    tabscintilla.h \
    tools.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
