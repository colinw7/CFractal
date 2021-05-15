TEMPLATE = lib

TARGET = CQFractal

DEPENDPATH += .

QT += widgets

CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

# Input
HEADERS += \
../qinclude/CQPointFractal.h \
\
CCubeHelix.h \
CQColorsDefPalettes.h \
CQColorsDefThemes.h \
CQColors.h \
CQColorsPalette.h \
CQColorsTheme.h \

SOURCES += \
CQPointFractal.cpp \
\
CQColors.cpp \
CQColorsDefPalettes.cpp \
CQColorsDefThemes.cpp \
CQColorsPalette.cpp \
CQColorsTheme.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../qinclude \
../include \
../../CQUtil/include \
../../CFont/include \
../../CImageLib/include \
../../CFile/include \
../../CUtil/include \
../../CMath/include \
../../CStrUtil/include \
../../CConfig/include \
../../CRegExp/include \
../../COS/include \
