TEMPLATE = app

QT += widgets printsupport webkitwidgets

TARGET = CQXmlMandelbrot

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++11

MOC_DIR = .moc

#CONFIG += debug

# Input
SOURCES += \
CQXmlMandelbrot.cpp \
CQMandelbrot.cpp \

HEADERS += \
CQXmlMandelbrot.h \
CQMandelbrot.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
../../CQXml/include \
../../CXML/include \
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
-L../../CQXml/lib \
-L../../CQStyleWidget/lib \
-L../../CQPropertyTree/lib \
-L../../CQColorPalette/lib \
-L../../CXML/lib \
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
-lCQXml -lCQPropertyTree -lCQStyleWidget -lCXML -lCQFractal -lCFractal \
-lCQUtil -lCQColorPalette -lCConfig -lCFont -lCImageLib \
-lCThread -lCFile -lCFileUtil -lCMath -lCUtil -lCStrUtil -lCOS -lCRegExp \
-ljpeg -lpng -ltre
