C_CC   = gcc
CPP_CC = g++

RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = ../obj
LIB_DIR = ../lib
BIN_DIR = ../bin

all: $(BIN_DIR)/CXSedona

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(BIN_DIR)/CXSedona

CPP_SRC = \
CXSedona.cpp \
CSedona.cpp \

CPP_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_SRC))

CPPFLAGS = \
-std=c++14 \
-I$(INC_DIR) -I../xinclude -I. \
-I../../CRenderer/xinclude \
-I../../CRenderer/include \
-I../../CXLib/include \
-I../../CImageLib/include \
-I../../CFont/include \
-I../../CFileUtil/include \
-I../../CFile/include \
-I../../CRGBName/include \
-I../../COS/include \
-I../../CStrUtil/include \
-I../../CMath/include \
-I../../CUtil/include \
-I../../CTimer/include \

LFLAGS = \
$(LEBUG) \
-L$(LIB_DIR) \
-L../../CRenderer/lib \
-L../../CXLib/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CArgs/lib \
-L../../CFileUtil/lib \
-L../../CFile/lib \
-L../../CRGBName/lib \
-L../../CMath/lib \
-L../../CThread/lib \
-L../../COS/lib \
-L../../CStrUtil/lib \
-L../../CConfig/lib \
-L../../CUtil/lib \
-L../../CRegExp/lib \
-L../../CTimer/lib \

LIBS = \
-lCXFractal -lCFractal -lCXRenderer -lCRenderer \
-lCXLib -lCConfig -lCImageLib -lCFont -lCTimer -lCArgs \
-lCRGBName -lCFileUtil -lCFile -lCThread -lCMath -lCUtil -lCOS -lCRegExp -lCStrUtil \
-lXt -lX11 -lpng -ljpeg -ltre -lfreetype -lpthread

.SUFFIXES: .cpp

$(CPP_OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CPP_CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

$(BIN_DIR)/CXSedona: $(CPP_OBJS)
	$(CPP_CC) -o $(BIN_DIR)/CXSedona $(CPP_OBJS) $(LFLAGS) $(LIBS)
