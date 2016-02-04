//
//  Relation.h
//  

#ifndef Relation_h
#define Relation_h

#include <stdio.h>
#include "AttributeList.h"
#include "Tuple.h"

class Relation {
public:
    string name;
    std::vector<Tuple> tuples;
    AttributeList attribute_list;
    string primary_keys[];

    Relation(
             string _name,
             string attribute_names[],         // Name of each attribute
             int    attribute_max_lengths[],   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string _primary_keys[]             // Collection of primary keys
    );
    
    void insert_tuple(string values[]);
    void insert_tuple(Tuple new_tuple);
    void delete_tuple(string att_names[], string values[]);
	int get_attribute_index( string att_name );
    bool attribute_exist(string att_name);
	int get_size();
	int get_num_attributes();
	void rename_attribute( string renamed, int index );
	string get_attribute_name( int index );
    bool compare(vector<int> &tuple_indexes, string comparison_value, string compare_operator, int index);
	auto get_cell(int attribute_index, int tuple_index);
    void insert_attribute( int original_att_index, Relation &original_relation);
	void rename_relation(string rename);
	void set_max(int original_max_lengths[], Relation &original_relation);
	int* get_max();
	int get_max_index(int i);
	std::vector<Tuple> get_tuples_vector();
	void set_tuples_vector(std::vector<Tuple> tuples_input);
	string* get_primary();
    void set_primary(string original_primary_keys[], Relation &original_relation);
};

#endif /* Relation_h */
