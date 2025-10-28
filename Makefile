
CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall

SRC = src/main.cpp src/server.cpp
OUT = bin/webserver

all:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -rf bin