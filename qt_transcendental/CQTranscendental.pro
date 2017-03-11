TEMPLATE = app

QT += widgets

TARGET = CQTranscendental

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++11

MOC_DIR = .moc

#CONFIG += debug

# Input
SOURCES += \
CQTranscendental.cpp \

HEADERS += \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
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
-L../../CFractal/lib \
-L../../CQUtil/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CThread/lib \
-L../../CMath/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../COS/lib \
-L../../CUtil/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCQFractal -lCFractal -lCQUtil -lCConfig -lCFont -lCImageLib \
-lCMath -lCThread -lCFile -lCFileUtil -lCUtil -lCStrUtil -lCOS -lCRegExp \
-ljpeg -lpng -ltre