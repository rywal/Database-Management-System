//
//  Relation.h
//  

#ifndef Relation_h
#define Relation_h

#include <stdio.h>

class Relation {
public:
    string relation_name;
    std::vector<Tuple> tuples;
    AttributeList attributes;
    string[] prim_keys;

    Relation(
             string name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    );
    
    void insert_tuple(string[] values);
    
	int get_attribute_index( string att_name );
    bool attribute_exist(string att_name);
	int get_size();
	void rename_attribute( string renamed, int index );
	string get_attribute_name( int index );
    bool compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int index);
	//----------UNDEFINED----------//
    Attribute get_attribute( int index );
    //void insert( Tuple &tup_name );//
    void insert( Attribute &att_name );
	auto get_cell(int attribute_index, int tuple_index);
};

#endif /* Relation_h */
