//
//  Attribute.h
//  
//
//  Created by Ryan Walters on 1/31/16.
//
//

#ifndef Attribute_h
#define Attribute_h

#include <stdio.h>

#include "Cell.h"

// Individual Attribute (column) in the Relation
class Attribute {
private:
    string name;
    int max_length;
    
public:
    Attribute() {};
    Attribute( string _name, int _max_length ) : name(_name), max_length(_max_length) {}
    string get_name(){ return name; }
    int get_max_length(){ return max_length; }
    void set_max_length( int _length ){ max_length = _length; }
    void set_name( string _name ){ name = _name; }
};

#endif /* Attribute_h */
