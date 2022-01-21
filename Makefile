CXX = g++
# CFLAGS = -Wall -I$(INCL) -g -fsanitize=address
CFLAGS = -Wall -I$(INCL) -g
LIBS = -ltesseract -lpthread $(OPENCV)
OPENCV = `pkg-config --cflags --libs opencv`

SRC  = src
INCL = include
OBJ  = bin

SRCS=$(wildcard $(SRC)/*.cpp)
INCLS=$(wildcard $(INCL)/*.h)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BIN=lpds


all: $(BIN)

$(BIN): $(OBJS) $(OBJ)
	$(CXX) $(CFLAGS) $(LIBS) $(OBJS)  -o $@ 

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLS)| $(OBJ)
	$(CXX) $(CFLAGS) $(LIBS) -c $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	rm -r $(OBJ)
	rm $(BIN)