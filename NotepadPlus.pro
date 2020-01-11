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
    EncodingMapper.cpp \
    buffer.cpp \
    configfile.cpp \
    xmlfile.cpp \
    dialog/idd_preference_box.cpp \
    languages.cpp \
    uilanguage.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp \
    pugixml/pugixml.cpp \
    tabscintilla.cpp \
    tools.cpp  \
    uchardet/CharDistribution.cpp \
    uchardet/JpCntx.cpp \
    uchardet/LangModels/LangArabicModel.cpp \
    uchardet/LangModels/LangBulgarianModel.cpp \
    uchardet/LangModels/LangCroatianModel.cpp \
    uchardet/LangModels/LangCzechModel.cpp \
    uchardet/LangModels/LangDanishModel.cpp \
    uchardet/LangModels/LangEsperantoModel.cpp \
    uchardet/LangModels/LangEstonianModel.cpp \
    uchardet/LangModels/LangFinnishModel.cpp \
    uchardet/LangModels/LangFrenchModel.cpp \
    uchardet/LangModels/LangGermanModel.cpp \
    uchardet/LangModels/LangGreekModel.cpp \
    uchardet/LangModels/LangHebrewModel.cpp \
    uchardet/LangModels/LangHungarianModel.cpp \
    uchardet/LangModels/LangIrishModel.cpp \
    uchardet/LangModels/LangItalianModel.cpp \
    uchardet/LangModels/LangLatvianModel.cpp \
    uchardet/LangModels/LangLithuanianModel.cpp \
    uchardet/LangModels/LangMalteseModel.cpp \
    uchardet/LangModels/LangPolishModel.cpp \
    uchardet/LangModels/LangPortugueseModel.cpp \
    uchardet/LangModels/LangRomanianModel.cpp \
    uchardet/LangModels/LangRussianModel.cpp \
    uchardet/LangModels/LangSlovakModel.cpp \
    uchardet/LangModels/LangSloveneModel.cpp \
    uchardet/LangModels/LangSpanishModel.cpp \
    uchardet/LangModels/LangSwedishModel.cpp \
    uchardet/LangModels/LangThaiModel.cpp \
    uchardet/LangModels/LangTurkishModel.cpp \
    uchardet/LangModels/LangVietnameseModel.cpp \
    uchardet/nsBig5Prober.cpp \
    uchardet/nsCharSetProber.cpp \
    uchardet/nsEUCJPProber.cpp \
    uchardet/nsEUCKRProber.cpp \
    uchardet/nsEUCTWProber.cpp \
    uchardet/nsEscCharsetProber.cpp \
    uchardet/nsEscSM.cpp \
    uchardet/nsGB2312Prober.cpp \
    uchardet/nsHebrewProber.cpp \
    uchardet/nsLatin1Prober.cpp \
    uchardet/nsMBCSGroupProber.cpp \
    uchardet/nsMBCSSM.cpp \
    uchardet/nsSBCSGroupProber.cpp \
    uchardet/nsSBCharSetProber.cpp \
    uchardet/nsSJISProber.cpp \
    uchardet/nsUTF8Prober.cpp \
    uchardet/nsUniversalDetector.cpp \
    uchardet/uchardet.cpp \
    winclass.cpp

HEADERS += \
    EncodingMapper.h \
    PluginsManager/plusmessage.h \
    Utf8.h \
    buffer.h \
    configfile.h \
    xmlfile.h \
    def_parameters.h \
    dialog/idd_preference_box.h \
    languages.h \
    uilanguage.h \
    mainwindow.h \
    parameters.h \
    pugixml/pugiconfig.hpp \
    pugixml/pugixml.hpp \
    tabscintilla.h \
    tools.h  \
    uchardet/CharDistribution.h \
    uchardet/JpCntx.h \
    uchardet/nsBig5Prober.h \
    uchardet/nsCharSetProber.h \
    uchardet/nsCodingStateMachine.h \
    uchardet/nsEUCJPProber.h \
    uchardet/nsEUCKRProber.h \
    uchardet/nsEUCTWProber.h \
    uchardet/nsEscCharsetProber.h \
    uchardet/nsGB2312Prober.h \
    uchardet/nsHebrewProber.h \
    uchardet/nsLatin1Prober.h \
    uchardet/nsMBCSGroupProber.h \
    uchardet/nsPkgInt.h \
    uchardet/nsSBCSGroupProber.h \
    uchardet/nsSBCharSetProber.h \
    uchardet/nsSJISProber.h \
    uchardet/nsUTF8Prober.h \
    uchardet/nsUniversalDetector.h \
    uchardet/nscore.h \
    uchardet/prmem.h \
    uchardet/uchardet.h \
    winclass.h

FORMS += \
    dialog/idd_preference_box.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    uchardet/README.TXT

#此段代码是手动添加外部库自动生成的，在编译时指定dll的位置：D:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin/
win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin/ -lqscintilla2_qt5
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin/ -lqscintilla2_qt5d
else:unix: LIBS += -LD:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin/ -lqscintilla2_qt5

INCLUDEPATH += D:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin
DEPENDPATH += D:/Qt/Qt5.13.0/5.13.0/mingw73_32/bin
