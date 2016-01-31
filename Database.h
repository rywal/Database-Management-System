//This header file will create a class for each 
#include <stdexcept>
#include <vector>


// Holds the individual data
class Cell {
private:
    string string_data;
    int int_data;
    int max_length;
    
    // TODO: define getters and setters for cell data
};

// Individual Attribute (column) in the Relation
class Attribute {
private:
    int index;
    string name;
    
public:
    int get_index();
    string get_name();
};

// Collection of Attributes within the Relation
class AttributeList {
    std::vector<Attribute> attributes;
};

// Collection of cells within a row (Tuple)
class Tuple {
    Cell cells[];

};

class Relation {	//Table that holds Columns and rows
//Vector<Attribute<Domain>> (I'm not sure what the type would be.)
//We would have to traverse through the Attribues, first, then we could select which Cell we want, by selecting the Tuple
//I think?


public:
    bool does_exist(string att_name){} //Used to see if an Attribute exists
    bool compare(string att_name, string compare_string, int index){} //Used to compare a string to each Domain in an Atrribute
    int get_size(){} //Used to get the number of Tuples in a Relation
    Atrribute get_att(int index){} //Used to get Attribute (data) at index (will possibly merge with ch_att_name?)
    void ch_att_name(string renamed, int index){} //Used to change Attribute name by index
    void insert(Tuple &tup_name){} //Used to insert a Tuple into a Relation
    void insert(string att_name){} //Used to insert an attribute into the next index of a Relation(possibly union instead??)
};

// A collection of tables
class Database {         //A collection of Tables
    //dynamic data structure for holding different relations
    //a function that creates a new relation
    
};
