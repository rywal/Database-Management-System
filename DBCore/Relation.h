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
    std::vector<string> primary_keys;

    Relation(
             string _name,
             vector<string> attribute_names,         // Name of each attribute
             vector<int> attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             std::vector<string> _primary_keys            // Collection of primary keys
    );
    
    void insert_tuple(vector<string> values);
    void insert_tuple(Tuple new_tuple);
	void insert_relation(Relation r);
    Relation delete_tuple(Relation &original_relation, string att_name, string compare_value, string compare_operator);
	int get_attribute_index( string att_name );
    bool attribute_exist(string att_name);
	int get_size();
	int get_num_attributes();
	void rename_attribute( string renamed, int index );
	string get_attribute_name( int index );
    bool compare(string comparison_value1, string compare_operator, string compare_value2);
    bool compare(vector<int> &tuple_indexes, string comparison_value, string compare_operator, int index);
    void insert_attribute( int original_att_index, Relation &original_relation);
	void rename_relation(string rename);
	void set_max(vector<int> original_max_lengths);
	vector<int> get_max();
	int  get_max_index(int i);
	void set_tuples_vector(std::vector<Tuple> tuples_input);
	std::vector<string> get_primary();
    void set_primary(std::vector<string> original_primary_keys);
    std::vector<string> get_primary_keys() { return primary_keys; }
};

#endif /* Relation_h */
