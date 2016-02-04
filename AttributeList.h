//
//  AttributeList.h
//
#ifndef AttributeList_h
#define AttributeList_h

#include <stdio.h>
#include <vector>
#include "Attribute.h"

// Collection of Attributes within the Relation
class AttributeList {
    public:
    Attribute *attributes;
    int num_attributes;
    AttributeList(int _num_attributes) { num_attributes = _num_attributes; attributes = new Attribute[num_attributes]; set_names(); set_maxes() }
    ~AttributeList() { delete[] attributes; }

    string*  names(){
		string *result = new string[num_attributes];
		for (int i=0; i<num_attributes; i++){
			result[i]=attributes[i].get_name();
		}
		return result;
	}
                                    
    int* maxes(){
		int *result = new int[num_attributes];
		for (int i=0; i<num_attributes; i++){
			result[i]=attributes[i].get_max_length();
		}
		return result;
	}
    
    string* combine_names(AttributeList a, AttributeList b){
        string *result = new string[a.num_attributes + b.num_attributes];
        
        for(int i=0; i < a.num_attributes; i++){
            result[i]= a.attributes[i].get_name();
        }
        
        for(int i=0; i < b.num_attributes; i++){
            result[i + (a.num_attributes-1) ] = b.attributes[i].get_name();
        }
        
        return result;
    }
    
    int* combine_max( AttributeList a, AttributeList b){
        int *result = new int[a.num_attributes + b.num_attributes];
        
        for(int i=0; i < a.num_attributes; i++){
            result[i] = a.attributes[i].get_max_length();
        }
        
        for(int i=0; i < b.num_attributes; i++){
            result[i + (a.num_attributes-1) ] = b.attributes[i].get_max_length();
        }
        
        return result;
    }
};

#endif /* AttributeList_h */
