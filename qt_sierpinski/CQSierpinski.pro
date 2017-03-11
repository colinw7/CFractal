TEMPLATE = app

QT += widgets

TARGET = CQSierpinski

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++11

MOC_DIR = .moc

#CONFIG += debug

# Input
SOURCES += \
CQSierpinski.cpp \

HEADERS += \
CQSierpinski.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
../../CRenderer/qinclude \
../../CRenderer/include \
../../CQUtil/include \
../../CRGBName/include \
../../CFont/include \
../../CImageLib/include \
../../CFile/include \
../../COS/include \
../../CUtil/include \
../../CMath/include \
../../CStrUtil/include \
../../CThread/include \

unix:LIBS += \
-L$$LIB_DIR \
-L../../CRenderer/lib \
-L../../CQUtil/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CThread/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../CRGBName/lib \
-L../../CMath/lib \
-L../../COS/lib \
-L../../CUtil/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCFractal -lCQRenderer -lCRenderer -lCQUtil -lCConfig -lCFont -lCImageLib \
-lCThread -lCFile -lCFileUtil -lCRGBName -lCMath -lCUtil -lCStrUtil -lCOS -lCRegExp \
-ljpeg -lpng -ltre -lfreetype
