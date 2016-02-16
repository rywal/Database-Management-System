#include <stdexcept>
#include <vector>
#include "Relation.h"

// Core Database Components
// ------------------------
// Created by: Ryan Walters, Jonathan Grimes, Nathan Blattman and Victor Vazquez
// Outlines the various components of the Core Database functionality

// A collection of tables
class Database {
public:
    string name;
    std::vector<Relation> relations;
    
    Database(string _name);
    Relation& get_relation(string name);
    Relation& get_relation(int index);
	int get_relation_index( string rel_name );
	void create_relation(string name, Relation a);
    void create_relation(string name, vector<string> attribute_names, vector<int> attribute_types, vector<string> primary_keys);
    std::vector<Tuple> show_relation(string relation_name);
    void insert_tuple(string relation_name);
    bool union_compatible(Relation a, Relation b);
    bool cross_compatible(Relation a, Relation b);
    Relation set_union(string name, Relation a, Relation b);
    Relation set_difference(string name, Relation a, Relation b);
    Relation cross_product(string name, Relation a, Relation b);
    std::vector<string> outputRelation(int index);
    bool save(int index);
    bool close();
	void EXIT(); 		//defined in database.cpp
    Relation select(string att_name, string compare_value, string compare_operator, Relation in_rel);
    Relation project(vector<string> att_names, Relation in_rel);
    Relation renaming(string out_name, vector<string> att_renames , Relation in_rel);
    void update(Relation &in_rel, string att_name, string compare_operator, string comparison_value, string update_name);	
    std::vector<Tuple> show(Relation relation_name);
	void print_relation(Relation relation_name);
};
