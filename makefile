CXX=g++
CXXFLAGS=-std=c++11 -Wextra -Wall -pedantic -O2
DEBUG=-g 
INCLUDE=-Iinclude

all: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) main.cpp

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(DEBUG) main.cpp