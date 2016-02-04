//
//  Tuple.h
//
#ifndef Tuple_h
#define Tuple_h
#include "Cell.h"
#include <stdio.h>
#include <vector>

// Collection of cells within a row (Tuple)
class Tuple {
private:
    vector<Cell>cells;
    int num_att;
    
public:
    Tuple( int _num_attributes );
    ~Tuple();
    int insert_value( int index, auto value, int max_length );
    int insert_cell( int index, Cell cell );
    Cell get_cell(int index);
    int num_attributes() { return num_att; }

    bool operator== (Tuple &b);
    bool operator!= (Tuple &b);
};

#endif /* Tuple_h */
