CC = g++
AR = ar
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = ../obj
LIB_DIR = ../lib

all: $(LIB_DIR)/libCFractal.a

SRC = \
CBarnsley.cpp \
CBifuricationLib.cpp \
CCircles.cpp \
CColorRange.cpp \
CDragon.cpp \
CDragonCurve.cpp \
CDragonOutline.cpp \
CDrawTree.cpp \
CIfs.cpp \
CJulia.cpp \
CLorenz.cpp \
CLorenzCalc.cpp \
CMandelbrot.cpp \
CMandelDiff.cpp \
CMandelPhoenix.cpp \
CNewton.cpp \
COrthogonal.cpp \
CPharaoh.cpp \
CPhoenix.cpp \
CPickover2D.cpp \
CPickoverCalc.cpp \
CPointFractal.cpp \
CPointFractalRenderer.cpp \
CSierpinski.cpp \
CTranscendental.cpp \
CTurtle.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++14 \
-I$(INC_DIR) \
-I../../CCeil/include \
-I../../CRenderer/include \
-I../../CImageLib/include \
-I../../CFont/include \
-I../../CThread/include \
-I../../CMath/include \
-I../../CFile/include \
-I../../CRGBName/include \
-I../../CStrUtil/include \
-I../../CGlob/include \
-I../../COS/include \
-I../../CUtil/include \

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(LIB_DIR)/libCFractal.a

$(OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

.SUFFIXES: .cpp

$(LIB_DIR)/libCFractal.a: $(OBJS)
	$(AR) crv $(LIB_DIR)/libCFractal.a $(OBJS)
