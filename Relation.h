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
    string name;
    std::vector<Tuple> tuples;
    int num_attributes;
    
    Relation(
             string name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    );
    
    bool attribute_exist(string att_name);
    bool compare(string att_name, auto comparison_value, int index);
    int get_size(){ return tuples.size(); }
    Atrribute get_attribute( int index );
    void rename_attribute( string renamed, int index );
    void insert( Tuple &tup_name );
    void insert( string att_name );
};

#endif /* Relation_h */
