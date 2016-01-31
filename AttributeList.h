//
//  AttributeList.hpp
//
#ifndef AttributeList_h
#define AttributeList_h

#include <stdio.h>

// Collection of Attributes within the Relation
class AttributeList {
    Attribute attributes[];
    
    AttributeList( int num_attributes );
};

#endif /* AttributeList_h */
