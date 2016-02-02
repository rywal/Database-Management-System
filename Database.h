#include <stdexcept>
#include <vector>
#include "Attribute.h"
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
    std::vector<Tuple> show_relation(string name);
    
    bool union_compatible(Relation a, Relation b);new
    Relation set_union(string name, Relation a, Relation b);
    Relation set_difference(string name, Relation a, Relation b);
    Relation cross_product(string name, Relation a, Relation b);

};
