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
    Cell(string data, int _max_length);
    bool   is_string(){ return max_length > 0 ? true : false; }
    string get_string_data();
    int    get_int_data();
    void   set_value(string value, bool is_string);
};

// Individual Attribute (column) in the Relation
class Attribute {
private:
    int    index;
    string name;
    
public:
    int    get_index();
    string get_name();
};

// Collection of Attributes within the Relation
class AttributeList {
    AttributeList();
    std::vector<Attribute> attributes;
};

// Collection of cells within a row (Tuple)
class Tuple {
private:
    Cell cells[];
    
public:
    Tuple();
    void insert_string_value(int index, string value);
    void insert_integer_value(int index, int value);
};

class Relation {
public:
    Relation(
             string[] attribute_names,         // Name of each attribute
             int[]    attribute_max_lengths,   // Max length of attribute string value. NOTE: Should be 0 if type if integer
             string[] primary_keys             // Collection of primary keys
    );
    bool does_exist(string att_name){} //Used to see if an Attribute exists
    bool compare(string att_name, string compare_string, int index){} //Used to compare a string to each Domain in an Atrribute
    int get_size(){} //Used to get the number of Tuples in a Relation
    Atrribute get_att(int index){} //Used to get Attribute (data) at index (will possibly merge with ch_att_name?)
    void ch_att_name(string renamed, int index){} //Used to change Attribute name by index
    void insert(Tuple &tup_name){} //Used to insert a Tuple into a Relation
    void insert(string att_name){} //Used to insert an attribute into the next index of a Relation(possibly union instead??)
};

// A collection of tables
class Database {
    
};