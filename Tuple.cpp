//
//  Tuple.cpp
//
#include "Tuple.h"
Tuple::Tuple( int _num_attributes ){
    num_att = _num_attributes;
}

Tuple::~Tuple(){
    
}

int Tuple::insert_value( int index, string value, int max_length ){
    if (index >= 0 && index < num_attributes()) {
        Cell new_cell(value, max_length);
        cells.push_back( new_cell );
        return 0;
    } else {
        return -1;
    }
}

Cell Tuple::get_cell(int index){ return cells[index];}

bool Tuple::operator== (Tuple &b){
	if (num_attributes()!=b.num_attributes()) return false;
	for (int i=0; i<num_attributes(); i++){
		if(cells[i]!=b.get_cell(i))return false;
	}
	return true;
}

bool Tuple::operator!= (Tuple &b){
	if (num_attributes()!=b.num_attributes()) return true;
        for (int i=0; i<num_attributes(); i++){
                if(cells[i]!=b.get_cell(i))return true;
        }
        return false;
}
	


int Tuple::insert_cell( int index, Cell cell ){
    std::vector<int>::iterator it;
    it = cells.begin();
    // Referenced this iterator example from http://www.cplusplus.com/reference/vector/vector/insert/
    
    cells.insert( (it + index), cell);
}
