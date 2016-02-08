//
//  Database.cpp
//
#include <iostream>
#include <algorithm>
#include "Database.h"

Database::Database(string _name){name = _name; std::cout << "Relations size is " << relations.size() << std::endl;}


Relation Database::get_relation(string name) {
    for (int i = 0; i < relations.size(); i++){
        if(relations[i].name == name)
            return relations[i];
    }
}

Relation Database::get_relation(int index) {
    return relations[index];
}

int Database::get_relation_index( string rel_name ){
		for (int i=0; i < relations.size();i++){
			if (relations[i].name == rel_name){
				return i;
			}
		}
		return -1; //DOES NOT EXIST
}

void Database::create_relation(string name, vector<string> attribute_names, vector<int> attribute_types, vector<string> primary_keys){
    Relation new_relation(name, attribute_names, attribute_types, primary_keys);
    relations.push_back(new_relation);
}

bool Database::union_compatible(Relation a, Relation b){
	
	if(a.get_num_attributes() == b.get_num_attributes()){
		for(int i=0; i < a.get_num_attributes(); i++){
            if(a.attribute_list.attributes[i].get_name() != b.attribute_list.attributes[i].get_name()) {
				return false;
            }
		return true;
        }
    } else {
        return false;
    }
    
    return false;
}

Relation Database::set_union(string name, Relation a, Relation b){
    vector<string> att_names = a.attribute_list.names();
    vector<int> att_lengths = a.attribute_list.maxes();

	if (union_compatible(a, b)){
		Relation result( name, att_names, att_lengths, a.primary_keys);
		for (int i = 0; i < a.tuples.size(); i++){
			Tuple temp(a.attribute_list.num_attributes());
			for (int j = 0; j < result.attribute_list.num_attributes(); j++)
				temp.insert_value( j, a.tuples[i].get_cell(j).get_data(), a.tuples[i].get_cell(j).get_max_length() );
			result.insert_tuple(temp);
		}
		for (int i=0; i < b.tuples.size(); i++){
			Tuple temp(b.attribute_list.num_attributes());
			for (int j=0; j < result.attribute_list.num_attributes(); j++)
				temp.insert_value( j, b.tuples[i].get_cell(j).get_data(), b.tuples[i].get_cell(j).get_max_length() );
			result.insert_tuple(temp);
		}
        
		return result;	
	}
	else{
        std::cout << "These relations are not union compatible\n";
	}
}

Relation Database::set_difference(string name, Relation a, Relation b){
    vector<string> att_names = a.attribute_list.names();
    vector<int> att_lengths = a.attribute_list.maxes();

	if( union_compatible(a, b)){
		int j;
		Relation result( name, att_names, att_lengths, a.primary_keys);
		Tuple temp(a.attribute_list.num_attributes());
		for (int i=0; i<a.tuples.size(); i++){
			for(j=0; j<b.tuples.size(); j++){ 
				if (a.tuples[i] == b.tuples[j])
		 			break;
			}
			if(a.tuples[i] != b.tuples[j]){
				temp.cells = a.tuples[i].cells;
				result.insert_tuple(temp);
			}
		}
		return result;			
	}
	else{
        std::cout << "These relations are not union-compatible, therefore I cannot compute the set difference\n";
	}
}

bool Database::cross_compatible(Relation a,Relation b){
	
	for(int i=0; i<a.get_num_attributes(); i++){
		for( int j=0; j<b.get_num_attributes(); j++){
			if(a.get_attribute_name(i)==b.get_attribute_name(j))
				return false;
		}
	}
	return true;
}

Relation Database::cross_product(string name, Relation a, Relation b){

	if (cross_compatible(a,b)){
        vector<string> prim_keys = a.primary_keys;
        prim_keys.insert( prim_keys.end(), b.primary_keys.begin(), b.primary_keys.end() );
		Relation result(name, a.attribute_list.combine_names(a.attribute_list, b.attribute_list), a.attribute_list.combine_max(a.attribute_list, b.attribute_list), prim_keys);
		Tuple temp (a.get_num_attributes()+ b.get_num_attributes());
		for (int i=0; i<a.get_num_attributes(); i++){
			for (int j=0; j<b.get_num_attributes(); j++){
				for (int k=0; k<temp.num_attributes(); k++){
					if (k<a.get_num_attributes())
						temp.insert_value(k, a.tuples[i].get_cell(k).get_data(), a.tuples[i].get_cell(k).get_max_length());
					else
						temp.insert_value(k, b.tuples[i].get_cell(k).get_data(), b.tuples[i].get_cell(k).get_max_length());
				}		
				result.insert_tuple( temp);
			}
		}
		return result;
	}
	else{
        std::cerr << "These relations are not compatible for using the cross product function. Rename the attributes in one of the relations.";
	}
}

Relation Database::select( string att_name, string compare_value, string compare_operator, Relation &in_rel ){
    Relation out_rel(in_rel.name, in_rel.attribute_list.names(), in_rel.attribute_list.maxes(), in_rel.primary_keys);
    
    int index = in_rel.get_attribute_index( att_name );
    vector<int> matching_tuples;
    
    in_rel.compare(matching_tuples, compare_value, compare_operator, index);
    
    if ( index > -1 ) {
        for (int t = 0; t < matching_tuples.size(); t++) {
            out_rel.insert_tuple( in_rel.tuples[ matching_tuples[t] ] );
        }
    }
    
    return out_rel;
}

Relation Database::project(vector<string> att_names, Relation &in_rel){
	Relation out_rel((in_rel.name + "_Projection"), att_names, in_rel.attribute_list.maxes(), in_rel.primary_keys);
    
    vector<int> max_lengths = in_rel.attribute_list.maxes();
    
    out_rel.set_primary(in_rel.get_primary_keys());
    out_rel.set_max(max_lengths);

	for(int i=0; i < att_names.size(); i++){
		if(in_rel.attribute_exist(att_names[i])){
			//add Attributes to out_rel
			out_rel.insert_attribute( in_rel.get_attribute_index(att_names[i]), in_rel);
		} else {
			printf ("%s attribute was not found.", att_names[i].c_str() );
		}
	}
//    cout << in_rel.tuples.size() << " and     " << att_names.size() << endl;
    for(int i = 0; i < in_rel.tuples.size(); i++){
        vector<string> values;
        for(int col = 0; col < att_names.size(); col++){
            values.push_back( in_rel.tuples[i].cells[in_rel.get_attribute_index(att_names[col])].get_data() );
            std::cout << "Cell " << col << " has value " << values[col] << "\n";
        }
        out_rel.insert_tuple(values);
    }
    
	return out_rel;
}

Relation Database::renaming(string out_name, vector<string> att_renames , Relation &in_rel){
	Relation out_rel(out_name, att_renames, in_rel.get_max(), in_rel.primary_keys);
	if(in_rel.attribute_list.num_attributes() != att_renames.size()){
		printf ("There was not enough Attributes given or in the Relation.");
	}
	else{
		out_rel.set_tuples_vector(in_rel.tuples); //copy table
		out_rel.set_primary(in_rel.primary_keys);
		for(int i=0; i < in_rel.attribute_list.num_attributes(); i++){
			out_rel.rename_attribute(att_renames[i],i);
		}
	}
	return out_rel;
}
void Database::update(Relation &in_rel, vector<string> att_names, vector<string> compare_operators, vector<string> comparison_values, vector<string> update_name){
	vector<int> tuple_indexes;
	for(int i = 0; i < att_names.size(); i++){
		in_rel.compare(tuple_indexes,comparison_values[i],compare_operators[i],in_rel.get_attribute_index(att_names[i]));
		for(int n = 0; n < tuple_indexes.size(); n++){
//            std::cout << "Updating to a new value " << update_name[i] << "\n";
			in_rel.tuples[n].cells[in_rel.get_attribute_index(att_names[i])].set_value(update_name[i]);
		}
		tuple_indexes.clear();
	}
}/*
void CLOSE(FILE *f){		This needs to close out the database
	fclose (f);
}
*/

void EXIT(){		//This closes out the application
	exit(0);
}

std::vector<Tuple> Database::show(Relation &relation_name){
	return relation_name.tuples;
}

void Database::print_relation(Relation &relation_name){
	printf ("\n-=-=-=-=-=BEGIN-=-=-=-=-\n");
	printf ("Relation name:%s \n", relation_name.name.c_str());
    std::cout << "Relation size " << relation_name.tuples.size() << std::endl;
    for(int k = 0; k < relation_name.tuples.size(); k++) {
		for(int i = 0; i < relation_name.tuples[k].num_attributes(); i++){
			printf("%-10s", relation_name.tuples[k].get_cell(i).get_data().c_str());
//            std::cout << "Tried to get cell " << k << " " << i << " with data " << relation_name.tuples[k].get_cell(i).get_data().c_str() << std::endl;
		}
		printf ("\n");
	}
    printf ("Primary Keys: ");
	if(relation_name.primary_keys.size()>0) {
		printf ("%s", relation_name.primary_keys[0].c_str());
        for(int i=1; i<relation_name.primary_keys.size(); i++){
            printf (", %s", relation_name.primary_keys[i].c_str());
		}
	}
	printf ("\n=-=-=-=-=-=END-=-=-=-=-=\n\n\n");
}
