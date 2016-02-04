//
//  Tuple.cpp
//
#include "Tuple.h"
Tuple::Tuple( int _num_attributes ){
    num_att = _num_attributes;
    vector<Cell>_cells(_num_attributes);
    cells=_cells;
}

Tuple::~Tuple(){
    delete [] cells;
}

int Tuple::insert_value( int index, auto value, int max_length ){
    if (index >= 0 && index < num_attributes()) {
        Cell new_cell = Cell(value, max_length);
        cells[index] = new_cell;
        return 0;
    } else {
        return -1;
    }
}

bool Tuple::operator== (Tuple &b){
	if (num_attributes()!=b.num_attributes()) return false;
	for (int i=0; i<num_attributes(); i++){
		if(cells[i]!=b.cells[i])return false;
	}
	return true;
}

bool Tuple::operator!= (Tuple &b){
	if (num_attributes()!=b.num_attributes()) return true;
        for (int i=0; i<num_attributes(); i++){
                if(cells[i]!=b.cells[i])return true;
        }
        return false;
}
	


int Tuple::insert_cell( int index, Cell cell ){
        cells[index] = cell;
}
