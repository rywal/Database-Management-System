//
//  Relation.h
//  

#ifndef Relation_h
#define Relation_h

#include <stdio.h>

class Relation {
public:
    string name;
    std::vector<Tuple> tuples;
    AttributeList attribute_list;
    string[] primary_keys;

    Relation(
             string _name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] _primary_keys             // Collection of primary keys
    );
    
    void insert_tuple(string[] values);
    void delete_tuple(string[] att_names, string[] values);
    
	int get_attribute_index( string att_name );
    bool attribute_exist(string att_name);
	int get_size();
	void rename_attribute( string renamed, int index );
	string get_attribute_name( int index );
    bool compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int index);
	auto get_cell(int attribute_index, int tuple_index);
    void insert_attribute( int original_att_index, Relation &original_relation);
	void rename_relation(string rename);
	int[] get_max();
	std::vector<Tuple> get_tuples_vector();
	void set_tuples_vector(std::vector<Tuple> tuples_input);
	string[] get_primary();
	void set_primary(string[] original_primary_keys, relation &original_relation);
};

#endif /* Relation_h */
