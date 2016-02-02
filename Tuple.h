//
//  Tuple.h
//
#ifndef Tuple_h
#define Tuple_h

#include <stdio.h>

// Collection of cells within a row (Tuple)
class Tuple {
private:
    Cell cells*;
    int num_attributes;
    
public:
    Tuple( int _num_attributes );
    ~Tuple();
    int insert_value( int index, auto value );
    Cell get_cell(int index);
};

#endif /* Tuple_h */
