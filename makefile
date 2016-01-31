# makefile
# added capability to use makefile in various environments without modifications
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++
else ifeq ($(UNAME), Darwin)
    cc = g++
else
    cc = g++-4.7
endif

all: coreengine

coreengine: main.cpp
	$(cc) -std=c++11 -g -o DBengine main.cpp
