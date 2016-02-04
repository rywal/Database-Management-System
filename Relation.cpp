//
//  Relation.cpp
//
#include "Relation.h"
Relation::Relation(string _name, string attribute_names[], int attribute_max_lengths[], string _primary_keys[]){
    name = _name;
    primary_keys = _primary_keys;
    
    attribute_list = AttributeList( attribute_names.size() );
    for (int i = 0; i < attribute_list.num_attributes; i++) {
        Attribute new_attribute( attribute_names[i], attribute_max_lengths[i] );
        attribute_list.attributes[i] = new_attribute;
    }
}

void Relation::insert_tuple(string values[]){
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

Relation Relation::delete_tuple(vector<string> att_names, vector<string> compare_values, vector<string> compare_operators, string and_or_gate){
    return set_difference(name+"_Deleted", this, select(attribute_list.attributes, compare_values, compare_operators, and_or_gate));
}

int Relation::get_attribute_index( string att_name ){
    for (int i=0; i < attribute_list.num_attributes;i++){
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

void Relation::rename_attribute( string renamed, int index ){ attribute_list.attributes[index] = renamed; }

string Relation::get_attribute_name( int index ){ return attribute_list.attributes[index]; }

bool Relation::compare(vector<int> &tuple_indexes, string comparison_value, string compare_operator, int attribute_index){
    for(int i=0; i < get_size(); i++){//Compare whole Attribute with an operator and value
        if((tuples[i].get_cell(attribute_index).get_data()).is_string()){
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
}

void Relation::insert_attribute( int original_att_index, Relation &original_relation){//With pre-defined columns
	for(int i=0; i < get_size(); i++){
		tuples[i].push_back(original_relation.get_cell(original_att_index,i))
	}
}

void Relation::rename_relation(string rename){relation_name = rename;}

void Relation::set_max(int original_max_lengths[], Relation &original_relation){
	for(int i=0;i<attribute_max_lengths; i++){
		attribute_list.attributes[i].set_max_length( original_relation.get_max_index(original_relation.get_attribute_index(i)) );
	}
}

int* Relation::get_max(){ return attribute_max_lengths; }

int Relation::get_max_index(int i){ return attribute_list.attributes[i].get_max_length(); }

void Relation::set_tuples_vector(std::vector<Tuple> tuples_input){ tuples=tuples_input; }

string* Relation::get_primary(){ return primary_keys; }

void Relation::set_primary(string original_primary_keys[], Relation &original_relation){
	for(int i = 0; i < original_primary_keys.size();i++){
		primary_keys[i] = get_attribute_name(original_relation.get_attribute_index(original_primary_keys[i]));
	}
}

std::vector<Tuple> show(Relation &relation_name){
	return relation_name.tuples;
}

void print_relation(Relation &relation_name){
	printf ("-=-=-=-=-=BEGIN-=-=-=-=-\n");
	printf ("Relation name:%s \n", relation_name.name);
	for(auto tuple : relation_name.tuples) {
		for(int i = 0; i < relation_name.tuples.size(); i++){
			printf("%-10s", tuple.get_cell(i).get_data());
		}
		printf ("\n");
	}
	printf ("Primary Keys: ")
	if(relation_name.primary_keys.size()>0){
		printf ("%s", relation_name.primary_keys[0];
		for(int i=1; i<relation_name.primary_keys.size(), i++){
			printf (", %s", relation_name.primary_keys[i]);
		}
	}
	printf ("=-=-=-=-=-=END-=-=-=-=-=\n");
}
