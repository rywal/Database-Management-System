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
    	int[] att_max_lengths= attribute_max_lengths;//ADDED UNDERSCORE
    	string[] prim_keys= primary_keys;
		num_attributes= attribute_names.size();
	}
	
	bool attribute_exist(string att_name){
		for (int i=0; i < att_names.size();i++){
			if (att_names[i] == att_name){
				return true;
			}
		} 
		return false;
	}
	
    bool compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int index);
	int get_length();//Number of Columns
    Attribute get_attribute( int index );
	int get_attribute_index( string att_name );
	string get_attribute_name( int index );
    void rename_attribute( string renamed, int index );
    void insert( Tuple &tup_name );
    void insert( Attribute &att_name );
	