//
//  Relation.h
//  
//
//  Created by Ryan Walters on 1/31/16.
//
//

#ifndef Relation_h
#define Relation_h

#include <stdio.h>

class Relation {
public:
    string relation_name;
    std::vector<Tuple> tuples;
    int num_attributes;
    string[] att_names;
    int[] att_max_lengths;
    string[] prim_keys;

    Relation(
             string name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    );
    
    bool attribute_exist(string att_name);
    bool compare(string att_name, auto comparison_value, int index);
    int get_size(){ return tuples.size(); }
    Attribute get_attribute( int index );
    void ch_att_name( string renamed, int index );
    void insert( Tuple &tup_name );
    void insert( string att_name );
};

#endif /* Relation_h */
