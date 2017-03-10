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
CMandelbrot.cpp \
CJulia.cpp \
CDragon.cpp \
CPhoenix.cpp \
CPointFractal.cpp \
CPointFractalRenderer.cpp \
CColorRange.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++11 \
-I$(INC_DIR) \
-I../../CThread/include \
-I../../CMath/include \
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
