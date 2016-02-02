//
//  Tuple.cpp
//
#include "Tuple.h"
Tuple::Tuple( int _num_attributes ){
    num_attributes = _num_attributes;
    cells = new Cell[num_attributes];
}

Tuple::~Tuple(){
    delete [] cells;
}

int Tuple::insert_cell( int index, Cell cell ){
        cells[index] = cell;
}