#include <stdexcept>
#include <vector>

// Core Database Components
// ------------------------
// Created by: Ryan Walters, Jonathan Grimes, Nathan Blattman and Victor Vazquez
// Outlines the various components of the Core Database functionality

// Holds the individual data
class Cell {
private:
    string string_data;
    int int_data;
    int max_length;
    
public:
    Cell( int _max_length );
    Cell( string data, int _max_length );
    bool   is_string(){ return max_length > 0 ? true : false; }
    bool   is_null();
    auto   get_data();
    int    set_value( string value );
    int    set_value( int value );
};

// Individual Attribute (column) in the Relation
class Attribute {
private:
    string name;
    
public:
    string get_name(){ return name; }
    void   set_name();
};

// Collection of Attributes within the Relation
class AttributeList {
    Attribute attributes[];
    
    AttributeList( int num_attributes );
};

// Collection of cells within a row (Tuple)
class Tuple {
private:
    Cell cells[];
    
public:
    Tuple( int num_attributes );
    void insert_value( int index, auto value );
};

class Relation {
public:
    string name;
    std::vector<Tuple> tuples;
    int num_attributes;
    
    Relation(
             string name,
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    );
    
    bool attribute_exist(string att_name);
    bool compare(string att_name, auto comparison_value, int index);
    int get_size(){ return tuples.size(); }
    Atrribute get_attribute( int index );
    void ch_att_name( string renamed, int index );
    void insert( Tuple &tup_name );
    void insert( string att_name );
};

// A collection of tables
class Database {
    string name;
    std::vector<Relation> relations;
    
    Database(string name);
};
