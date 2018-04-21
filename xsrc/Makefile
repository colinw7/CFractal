CC = g++
AR = ar
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../xinclude
OBJ_DIR = ../obj
LIB_DIR = ../lib

all: $(LIB_DIR)/libCXFractal.a

SRC = \
CXPointFractal.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
--std=c++14 \
-I$(INC_DIR) \
-I../include \
-I../../CRenderer/xinclude \
-I../../CRenderer/include \
-I../../CXLib/include \
-I../../CImageLib/include \
-I../../CFont/include \
-I../../CConfig/include \
-I../../COS/include \
-I../../CFile/include \
-I../../CStrUtil/include \
-I../../CMath/include \
-I../../CTimer/include \
-I../../CUtil/include \
-I.

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(LIB_DIR)/libCXFractal.a

$(OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CDEBUG) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

.SUFFIXES: .cpp

$(LIB_DIR)/libCXFractal.a: $(OBJS)
	$(AR) crv $(LIB_DIR)/libCXFractal.a $(OBJS)
