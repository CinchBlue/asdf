CXX=g++
CXXFLAGS=-std=c++11 -Wextra -Wall -pedantic -O2
DEBUG=-g 

all: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) main.cpp