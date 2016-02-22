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
    for(int i = 0; i < primary_keys.size(); i++){
//        cout << "Primary key copied: " << primary_keys[i] << "\n";
    }
    for (int i = 0; i < attribute_names.size(); i++) {
        Attribute new_attribute( attribute_names[i], attribute_max_lengths[i] );
        attribute_list.attributes.push_back( new_attribute );
//        std::cout << "Pushed back attribute: " << new_attribute.get_name() << " with size: " << new_attribute.get_max_length() << "\n";
    }
}

void Relation::insert_tuple(vector<string> values){
//    std::cout << values.size() << "Values " << attribute_list.num_attributes() << " num attributes\n";
    if (values.size() == attribute_list.num_attributes()) {
        Tuple new_tuple( values.size() );
        for (int i = 0; i < values.size(); i++){
		   Cell new_cell( values[i], attribute_list.attributes[i].get_max_length() ); 
            new_tuple.insert_cell(i, new_cell);
        }
        this->tuples.push_back(new_tuple);
    }
}

void Relation::insert_tuple(Tuple new_tuple){
	tuples.push_back(new_tuple);
}

void Relation::insert_relation(Relation r){
		r.get_num_attributes();
		if(r.get_num_attributes()==attribute_list.num_attributes()) {
			for(int i=0; i<r.get_num_attributes(); i++){
				if(r.get_attribute_name(i)!=get_attribute_name(i)) {
					cerr<<"An attribute given did not match the cooresponding attribute in the original relation\n";
					return;
				}
			}
			for(int j=0; j<r.get_size(); j++){
						tuples.push_back(r.tuples[j]);
			}
		}
			else
				cerr<<"The attribute_lists did not have the same number of elements\n";
}

Relation Relation::delete_tuple(Relation &original_relation, string att_name, string compare_value, string compare_operator){
    Database db("name");
    return db.set_difference(name+"_Deleted", original_relation, db.select(att_name, compare_value, compare_operator, original_relation));
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

string Relation::get_attribute_name( int index ){ return attribute_list.attributes[index].get_name(); }

// Referenced from http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool Relation::compare(string comparison_value1, string compare_operator, string comparison_value2){
        if(compare_operator == "le"){
            return comparison_value1 < comparison_value2;
        }else if(compare_operator == "leq"){
           	return comparison_value1 <= comparison_value2;
        }else if(compare_operator == "eq"){
            return comparison_value1 == comparison_value2;
        }else if(compare_operator == "geq"){
            return comparison_value1 >= comparison_value2;
        }else if(compare_operator == "gr"){
            return comparison_value1 > comparison_value2;
        }else if(compare_operator == "neq"){
            return comparison_value1 != comparison_value2;
        }
    return false;
}


bool Relation::compare(vector<int> &tuple_indexes, string comparison_value, string compare_operator, int attribute_index){
    for(int i=0; i < get_size(); i++){//Compare whole Attribute with an operator and value
        if(compare_operator == "le"){
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
        }else if(compare_operator == "neq"){
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
        std::cout << original_relation.tuples[i].get_cell(original_att_index).get_data() << " attribute has value " << original_relation.tuples[i].get_cell(original_att_index).get_max_length() << "\n";
	}
}

void Relation::rename_relation(string rename){ name = rename; }

void Relation::set_max(vector<int> original_max_lengths){
	for(int i=0; i < original_max_lengths.size(); i++){
		attribute_list.attributes[i].set_max_length(original_max_lengths[i]);
	}
}

vector<int> Relation::get_max(){ return attribute_list.maxes(); }

int Relation::get_max_index(int i){ return attribute_list.attributes[i].get_max_length(); }

void Relation::set_tuples_vector(std::vector<Tuple> tuples_input){ tuples = tuples_input; }

std::vector<string> Relation::get_primary(){ return primary_keys; }

void Relation::set_primary(std::vector<string> original_primary_keys){
    primary_keys = original_primary_keys;
}
