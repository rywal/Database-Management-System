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
		relation_name = name;
		att_names = attribute_names;
    	att_max_lengths= attribute_max_lengths;//ADDED UNDERSCORE
    	prim_keys= primary_keys;
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
	
	int get_attribute_index( string att_name ){
		for (int i=0; i < att_names.size();i++){
			if (att_names[i] == att_name){
				return i;
			}
		}
		return -1; //ERROR!! (DOES NOT EXIST)
	}
	
	int get_size(){ return tuples.size(); }
	
	void rename_attribute( string renamed, int index ){att_names[index] = renamed;}
	
    string get_attribute_name( int index ){return att_names[index];}
	
	
	bool compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int index){
		for(int i=0; i < this.num_attributes; i++){
			
		}
		
	}
	
	
	

    Attribute get_attribute( int index );
	
	
	auto get_cell(int attribute_index, int tuple_index);
	
    void insert( Tuple &tup_name );
    void insert( Attribute &att_name );
	