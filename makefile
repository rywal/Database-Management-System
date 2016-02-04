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

Attribute: Attribute.h Attribute.cpp
$(cc) -std=c++14 -c -g Attribute.cpp

AttributeList: AttributeList.h AttributeList.cpp Attribute.o
$(cc) -std=c++14 -c -g Attribute.cpp Attribute.o

Tuple: Tuple.h Tuple.cpp Cell.o
$(cc) -std=c++14 -c -g Tuple.cpp Cell.o

Relation: Relation.h Relation.cpp Tuple.o AttributeList.o
$(cc) -std=c++14 -c -g Relation.cpp Tuple.o AttributeList.o

Database: Database.h Database.cpp Relation.o
$(cc) -std=c++14 -c -g Database.cpp Relation.o

test: test Database.o
$(cc) -std=c++11 -g -o test test.cpp Database.o