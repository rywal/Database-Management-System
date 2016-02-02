//
//  Relation.cpp
//
#include "Relation.h"
Relation::Relation(string name, string[] attribute_names, int[] attribute_max_lengths, string[] primary_keys){
    relation_name = name;
    att_names = attribute_names;
    att_max_lengths= attribute_max_lengths;
    prim_keys= primary_keys;
    num_attributes= attribute_names.size();
}

void Relation::insert_tuple(string[] values){
    if (values.size() == attributes.num_attributes) {
        Tuple new_tuple( values.size() );
        
        for (int i = 0; i < values.size(); i++){
            Cell new_cell( values[i], attributes[i].max_length );
            new_tuple.insert_cell(i, new_cell);
        }
        
        tuples.push_back(new_tuple);
    }
}

int get_attribute_index( string att_name ){
    for (int i=0; i < att_names.size();i++){
        if (att_names[i] == att_name){
            return i;
        }
    }
    return -1; //ERROR!! (DOES NOT EXIST)
}


bool attribute_exist(string att_name){
    return (get_attribute_index(att_name) == -1);
}

int get_size(){ return tuples.size(); }

void rename_attribute( string renamed, int index ){ att_names[index] = renamed; }

string get_attribute_name( int index ){ return att_names[index]; }


bool compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int index){
    for(int i=0; i < /*NUMBER OF ROWS*/; i++){
        if((get_cell(index, i)).is_string()){
            if(comparison_value == get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "le"){
            if (comparison_value < get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "leq"){
            if (comparison_value <= get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "eq"){
            if (comparison_value == get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "geq"){
            if (comparison_value >= get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "gr"){
            if (comparison_value > get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "ne"){
            if (comparison_value != get_cell(index, i)){
                tuple_indexes.push_back(i);
            }
        }
    }
}

//----------UNDEFINED----------//
Attribute get_attribute( int index );
auto get_cell(int attribute_index, int tuple_index);
//void insert( Tuple &tup_name );//
void insert( Attribute &att_name );
//----------UNDEFINED----------//