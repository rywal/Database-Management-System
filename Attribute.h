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

// Individual Attribute (column) in the Relation
class Attribute {
private:
    string name;
    
public:
    string get_name(){ return name; }
    void   set_name();
};

// Collection of Attributes within the Relation
class AttributeList {
    Attribute attributes[];
    
    AttributeList( int num_attributes );
};

#endif /* Attribute_h */
