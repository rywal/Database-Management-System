# makefile
# added capability to use makefile in various environments without modifications
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++ -I/usr/local/boost
else ifeq ($(UNAME), Darwin)
    cc = g++
else
    cc = g++-4.7
endif

.PHONY: all DBCore Parser Parser2 Application clean

all: DBCore Parser

DBCore:
	$(cc) -std=c++11 -g -o run-dbcore DBCore/Cell.cpp  DBCore/Database.cpp  DBCore/Relation.cpp  DBCore/test.cpp  DBCore/Tuple.cpp

Parser:
	$(cc) -std=c++11 -g -o run-parser DBCore/Cell.cpp  DBCore/Database.cpp  DBCore/Relation.cpp DBCore/Tuple.cpp Parser/ryanparser.cpp
	
Parser2:
	$(cc) -std=c++11 -g -o run-parser2 DBCore/Cell.cpp  DBCore/Database.cpp  DBCore/Relation.cpp DBCore/Tuple.cpp Parser/run_parser.cpp

Application:
	$(cc) -std=c++11 -g -o run-app DBCore/Cell.cpp  DBCore/Database.cpp  DBCore/Relation.cpp  Application/app.cpp  DBCore/Tuple.cpp

clean:
	rm -f run-dbcore run-parser run-app *.db *.o a.out
