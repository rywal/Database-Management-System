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

all: test Cell Attribute AttributeList Tuple Relation Database

Cell: Cell.h Cell.cpp
$(cc) -std=c++14 -c -g Cell.cpp

Tuple: Tuple.h Tuple.cpp Cell.o
$(cc) -std=c++14 -c -g Tuple.cpp Cell.o

Relation: Relation.h Relation.cpp Tuple.o
$(cc) -std=c++14 -c -g Relation.cpp Tuple.o

Database: Database.h Database.cpp Relation.o Tuple.o
$(cc) -std=c++14 -c -g Database.cpp Relation.o Tuple.o

test: test Database.o
$(cc) -std=c++14 -g -o test test.cpp Database.o