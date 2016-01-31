//
//  Tuple.h
//
#ifndef Tuple_h
#define Tuple_h

#include <stdio.h>

// Collection of cells within a row (Tuple)
class Tuple {
private:
    Cell cells[];
    
public:
    Tuple( int num_attributes );
    void insert_value( int index, auto value );
};

#endif /* Tuple_h */
