CPP_FILES=main.cpp socket_sources/socket_class.cpp
CXX=g++
OUT=main.o
LIBS=""
FLAGS=--std=c++17

all:
	$(CXX) $(CPP_FILES) $(FLAGS) -o $(OUT)
