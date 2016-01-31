//
//  Relation.cpp
//
#include "Relation.h"
Relation::Relation(
             string name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    ){
	relation_name= name;
	string[] att_names= attribute_names;
    	int[] att_max_lengths= attribute_max lengths;
    	string[] prim_keys= primary_keys;
	num_attributes= attribute_names.size();
}