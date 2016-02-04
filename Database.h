#include <stdexcept>
#include <vector>
#include "Relation.h" 

// Core Database Components
// ------------------------
// Created by: Ryan Walters, Jonathan Grimes, Nathan Blattman and Victor Vazquez
// Outlines the various components of the Core Database functionality

// A collection of tables
class Database {
private:
    string name;
    std::vector<Relation> relations;
    
public:
    Database(string _name);
	int get_relation_index( string rel_name );
    void create_relation(string name, string attribute_names[], int attribute_types[], string primary_keys[]);
    std::vector<Tuple> show_relation(string relation_name);
    void insert_tuple(string relation_name);
    bool union_compatible(Relation a, Relation b);
    bool cross_compatible(Relation a, Relation b);
    Relation set_union(string name, Relation a, Relation b);
    Relation set_difference(string name, Relation a, Relation b);
    Relation cross_product(string name, Relation a, Relation b);
	// void CLOSE(FILE *f);	needs to be defined in database.cpp
	void EXIT(); 		//defined in database.cpp
    Relation select(vector<string> att_names, vector<string> compare_values, vector<string> compare_operators, Relation &in_rel, string and_or_gate[]);
    Relation project(vector<string> att_names, Relation &in_rel);
    Relation renaming(string out_name, vector<string> att_renames , Relation &in_rel);
	std::vector<Tuple> show(Relation &relation_name);
	void print_relation(Relation &relation_name);
};
