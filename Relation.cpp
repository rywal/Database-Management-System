//
//  Relation.cpp
//
#include <iostream>
#include <algorithm>
#include "Relation.h"
#include "Database.h"

Relation::Relation(string _name, vector<string> attribute_names, vector<int> attribute_max_lengths, std::vector<string> _primary_keys){
    name = _name;
    primary_keys = _primary_keys;
    for (int i = 0; i < attribute_names.size(); i++) {
        Attribute new_attribute( attribute_names[i], attribute_max_lengths[i] );
        attribute_list.attributes.push_back( new_attribute );
//        std::cout << "Pushed back attribute: " << new_attribute.get_name() << "\n";
    }
}

void Relation::insert_tuple(vector<string> values){
//    std::cout << values.size() << "Values " << attribute_list.num_attributes() << " num attributes\n";
    if (values.size() == attribute_list.num_attributes()) {
        Tuple new_tuple( values.size() );
        
        for (int i = 0; i < values.size(); i++){
//            std::cout << attribute_list.attributes[i].get_name() << "(" << values[i] << ") Length: " << attribute_list.attributes[i].get_max_length() << std::endl;
            Cell new_cell( values[i], attribute_list.attributes[i].get_max_length() );
            new_tuple.insert_cell(i, new_cell);
			
			
			
//			std::cout<<"THIS IS A TUPLE(INSIDE): (index)"<< i << "\n now the rest: ";
			for (int i = 0; i < tuples.size(); i++){
				std::cout << new_tuple.get_cell(i).get_data().c_str() << "  " << new_cell.get_data().c_str();
				//std::count<< " direct: " << new_tuple->cells[i]<< " ";
			}
//			std::cout<<"\nTHIS IS THE END\n\n";
			
        }
//        std::cout<<"THIS IS A TUPLE: ";
		for (int i = 0; i < tuples.size(); i++){
			std::cout << new_tuple.get_cell(i).get_data().c_str() << "  ";
		}
//		std::cout<<"THIS IS THE END\n";
        tuples.push_back(new_tuple);
    }
}

void Relation::insert_tuple(Tuple new_tuple){
	tuples.push_back(new_tuple);
}

Relation Relation::delete_tuple(Relation &original_relation, vector<string> att_names, vector<string> compare_values, vector<string> compare_operators, vector<string> and_or_gate){
    Database db("name");
    return db.set_difference(name+"_Deleted", original_relation, db.select(att_names, compare_values, compare_operators, original_relation, and_or_gate));
}

int Relation::get_attribute_index( string att_name ){
    for (int i=0; i < attribute_list.num_attributes();i++){
        if (attribute_list.attributes[i].get_name() == att_name){
            return i;
        }
    }
    return -1; //DOES NOT EXIST
}

bool Relation::attribute_exist(string att_name){
    return (get_attribute_index(att_name) != -1);
}

int Relation::get_size(){ return tuples.size(); }

int Relation::get_num_attributes(){return attribute_list.num_attributes();}

void Relation::rename_attribute( string renamed, int index ){ attribute_list.attributes[index].set_name(renamed); }

string Relation::get_attribute_name( int index ){ return attribute_list.attributes[index]; }

// Referenced from http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool Relation::compare(vector<int> &tuple_indexes, string comparison_value, string compare_operator, int attribute_index){
    for(int i=0; i < get_size(); i++){//Compare whole Attribute with an operator and value
       // if( isdigit(tuples[i].get_cell(attribute_index).get_data()) ){
        if( is_number( tuples[i].get_cell(attribute_index).get_data() ) ){
            if(comparison_value == tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "le"){
            if (comparison_value < tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "leq"){
            if (comparison_value <= tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "eq"){
            if (comparison_value == tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "geq"){
            if (comparison_value >= tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "gr"){
            if (comparison_value > tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }else if(compare_operator == "ne"){
            if (comparison_value != tuples[i].get_cell(attribute_index).get_data()){
                tuple_indexes.push_back(i);
            }
        }
    }
    return true;
}

void Relation::insert_attribute( int original_att_index, Relation &original_relation){//With pre-defined columns
	for(int i=0; i < get_size(); i++){
        tuples[i].insert_value(i, original_relation.tuples[i].get_cell(original_att_index).get_data(), original_relation.tuples[i].get_cell(original_att_index).get_max_length());
	}
}

void Relation::rename_relation(string rename){ name = rename; }

void Relation::set_max(vector<int> original_max_lengths, Relation &original_relation){
	for(int i=0; i<get_num_attributes(); i++){
		attribute_list.attributes[i].set_max_length( original_relation.get_max_index(original_relation.get_attribute_index(to_string(i))) );
	}
}

vector<int> Relation::get_max(){ return attribute_list.maxes(); }

int Relation::get_max_index(int i){ return attribute_list.attributes[i].get_max_length(); }

void Relation::set_tuples_vector(std::vector<Tuple> tuples_input){ tuples = tuples_input; }

std::vector<string> Relation::get_primary(){ return primary_keys; }

void Relation::set_primary(std::vector<string> original_primary_keys, Relation &original_relation){
	for(int i = 0; i < original_primary_keys.size();i++){
		primary_keys[i] = get_attribute_name(original_relation.get_attribute_index(original_primary_keys[i]));
	}
}
