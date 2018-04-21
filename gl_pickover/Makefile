CC = g++
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = .
LIB_DIR = ../lib
BIN_DIR = ../bin

all: $(BIN_DIR)/CGLPickover

SRC = \
CGLPickover.cpp

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++14 \
-I$(INC_DIR) \
-I. \
-I../../CGL/app_include \
-I../../CGeometry3D/include \
-I../../CRenderer/gl_include \
-I../../CRenderer/include \
-I../../CImageLib/include \
-I../../CFont/include \
-I../../CMath/include \
-I../../CFile/include \
-I../../CStrUtil/include \
-I../../COS/include \
-I../../CUtil/include \

LFLAGS = \
-L$(LIB_DIR) \
-L../../CGL/lib \
-L../../CGeometry3D/lib \
-L../../CFractal/lib \
-L../../CRenderer/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CConfig/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../CMath/lib \
-L../../CUtil/lib \
-L../../CRegExp/lib \
-L../../CStrUtil/lib \
-L../../COS/lib \

LIBS = \
-lCGLApp \
-lCGLRenderer \
-lCGeometry3D \
-lCFractal \
-lCRenderer \
-lCImageLib \
-lCFont \
-lCConfig \
-lCFile \
-lCFileUtil \
-lCMath \
-lCUtil \
-lCRegExp \
-lCStrUtil \
-lCOS \
-lglut -lGLU -lGL \
-lfreetype -ltre -lboost_signals \
-ljpeg -lpng

clean:
	$(RM) -f *.o
	$(RM) -f CGLPickover

.SUFFIXES: .cpp

.cpp.o:
	$(CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

$(BIN_DIR)/CGLPickover: $(OBJS)
	$(CC) $(LDEBUG) -o $(BIN_DIR)/CGLPickover $(OBJS) $(LFLAGS) $(LIBS)
