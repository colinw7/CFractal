TEMPLATE = app

QT += widgets

TARGET = CQIfs

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

#CONFIG += debug

# Input
SOURCES += \
CQIfs.cpp \
CQTurtle.cpp \

HEADERS += \
CQIfs.h \
CQTurtle.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
../../CCeil/include \
../../CRenderer/include \
../../CQUtil/include \
../../CFont/include \
../../CImageLib/include \
../../CFile/include \
../../COS/include \
../../CUtil/include \
../../CMath/include \
../../CRGBName/include \
../../CStrUtil/include \
../../CGlob/include \
../../CThread/include \

unix:LIBS += \
-L$$LIB_DIR \
-L../../CCeil/lib \
-L../../CQUtil/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CThread/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../CMath/lib \
-L../../CRGBName/lib \
-L../../COS/lib \
-L../../CUtil/lib \
-L../../CGlob/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCFractal -lCCeil -lCQUtil -lCConfig -lCFont -lCImageLib -lCThread \
-lCFile -lCFileUtil -lCMath -lCUtil -lCGlob -lCStrUtil -lCRGBName -lCOS -lCRegExp \
-ljpeg -lpng -ltre
