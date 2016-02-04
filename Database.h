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
    Database(string name);
    void create_relation(string name, string[] attribute_names, int[] attribute_types, string[] primary_keys);
    std::vector<Tuple> show_relation(string relation_name);
    void insert_tuple(string relation_name);
    bool union_compatible(Relation a, Relation b);
    bool cross_compatible(Relation a, Relation b);
    Relation set_union(string name, Relation a, Relation b);
    Relation set_difference(string name, Relation a, Relation b);
    Relation cross_product(string name, Relation a, Relation b);
    Relation select(vector<string> att_names, vector<auto> compare_values, vector<string> compare_operators, Relation &in_rel, vector<string> and_or_gate));
    Relation Project(vector<string> att_names, Relation &in_rel);
    Relation Renaming(String out_rel, vector<string> att_renames , Relation &in_rel);
};	

