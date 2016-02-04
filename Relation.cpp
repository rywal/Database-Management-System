//
//  Relation.cpp
//
#include "Relation.h"
Relation::Relation(string name, string[] attribute_names, int[] attribute_max_lengths, string[] _primary_keys){
    relation_name = name;
    primry_keys = _primary_keys;
    
    attribute_list = AttributeList( attribute_names.size() );
    for (int i = 0; i < attribute_list.num_attributes; i++) {
        Attribute new_attribute( attribute_names[i], attribute_max_lengths[i] );
        attribute_list.attributes[i] = new_attribute;
    }
}

void Relation::insert_tuple(string[] values){
    if (values.size() == attribute_list.num_attributes) {
        Tuple new_tuple( values.size() );
        
        for (int i = 0; i < values.size(); i++){
            Cell new_cell( values[i], attribute_list.attributes[i].max_length );
            new_tuple.insert_cell(i, new_cell);
        }
        
        tuples.push_back(new_tuple);
    }
}

void Relation::insert_tuple(Tuple new_tuple){
	tuples.push_back(new_tuple);
}

void Relation::delete_tuple(string[] conditions){
    
    for (auto tuple : tuples) {
        for (int i = 0; i < attribute_indices.size(); i++){
            
        }
    }
}

int Relation::get_attribute_index( string att_name ){
    for (int i=0; i < attribute_names.size();i++){
        if (attribute_names[i] == att_name){
            return i;
        }
    }
    return -1; //DOES NOT EXIST
}


bool Relation::attribute_exist(string att_name){
    return (get_attribute_index(att_name) == -1);
}

int Relation::get_size(){ return tuples.size(); }

int Relation::get_num_attributes(){return attribute_list.num_attribute;}

void Relation::rename_attribute( string renamed, int index ){ attribute_names[index] = renamed; }

string Relation::get_attribute_name( int index ){ return attribute_names[index]; }

bool Relation::compare(vector<int> &tuple_indexes, auto comparison_value, string compare_operator, int attribute_index){
    for(int i=0; i < get_size(); i++){//Compare whole Attribute with an operator and value
        if((get_cell(index, i)).is_string()){
            if(comparison_value == get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "le"){
            if (comparison_value < get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "leq"){
            if (comparison_value <= get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "eq"){
            if (comparison_value == get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "geq"){
            if (comparison_value >= get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "gr"){
            if (comparison_value > get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "ne"){
            if (comparison_value != get_cell(attribute_index, i)){
                tuple_indexes.push_back(i);
            }
        }
    }
}

auto Relation::get_cell(int attribute_index, int tuple_index){
	return tuples[tuple_index].cells[attribute_index];
}

void Relation::insert_attribute( int original_att_index, Relation &original_relation){//With pre-defined columns
	for(int i=0; i < get_size(); i++){
		tuples[i].push_back(original_relation.get_cell(original_att_index,i))
	}
}

void Relation::rename_relation(string rename){relation_name = rename;}

void Relation::set_max(int[] original_max_lengths, relation &original_relation){
	for(int i=0;i<attribute_max_lengths; i++){
		attribute_max_lengths[i] = original_relation.get_max_index(original_relation.get_attribute_index(i));
	}
}

int[] Relation::get_max(){return attribute_max_lengths;}

int Relation::get_max_index(int i){return attribute_max_lengths[i];}

std::vector<Tuple> Relation::get_tuples_vector(){return tuples;}

void Relation::set_tuples_vector(std::vector<Tuple> tuples_input){tuples=tuples_input;}

string[] Relation::get_primary(){return primary_keys;}

void Relation::set_primary(string[] original_primary_keys, relation &original_relation){
	for(int i = 0; i < original_primary_keys.size();i++){
		primary_keys[i] = get_attribute_name(original_relation.get_attribute_index(original_primary_keys[i]));
	}
}
