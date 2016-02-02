//
//  AttributeList.hpp
//
#ifndef AttributeList_h
#define AttributeList_h

#include <stdio.h>
#include <vector>

// Collection of Attributes within the Relation
class AttributeList {
    Attribute attributes*;
    int num_attributes;
    
    AttributeList(int _num_attributes) { num_attributes = _num_attributes; attributes = new Attribute[num_attributes]; }
    ~AttributeList() { delete [] attributes; }
};

#endif /* AttributeList_h */
