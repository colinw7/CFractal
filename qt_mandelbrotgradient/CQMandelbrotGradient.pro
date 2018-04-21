TEMPLATE = app

QT += widgets

TARGET = CQMandelbrotGradient

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

#CONFIG += debug

# Input
SOURCES += \
CQMandelbrotGradient.cpp \

HEADERS += \
CQMandelbrotGradient.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
../../CQGradientPalette/include \
../../CExpr/include \
../../CFractal/qinclude \
../../CFractal/include \
../../CQUtil/include \
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
-L../../CQGradientPalette/lib \
-L../../CExpr/lib \
-L../../CFractal/lib \
-L../../CQUtil/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CThread/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../CMath/lib \
-L../../COS/lib \
-L../../CUtil/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCQGradientPalette -lCExpr \
-lCQFractal -lCFractal -lCQUtil -lCConfig -lCFont -lCImageLib \
-lCThread -lCFile -lCFileUtil -lCMath -lCUtil -lCStrUtil -lCOS -lCRegExp \
-ljpeg -lpng -ltre
