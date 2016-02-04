//
//  Database.cpp
//
#include "Database.h"

Database::Database(string name){
    
}

void Database::create_relation(string name, string attribute_names[], int attribute_types[], string primary_keys[]){
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
}

Relation Database::set_union(string name, Relation a, Relation b){
    string att_names* = new string[a.attribute_list.num_attributes];
    int att_max_lengths* = new int[a.attribute_list.num_attributes];
    
    for (int i = 0; i < a.attribute_list.num_attributes; i++){
        att_names[i] = a.attribute_list.attributes[i].get_name();
        att_max_lengths[i] = a.attribute_list.attributes[i].get_max_length();
    }

	if (union_compatible(a, b)){
		Relation result( name, att_names, att_max_lengths, a.primary_keys);
		for (int i = 0; i < a.tuples.size(); i++){
			Tuple temp(a.num_attributes);
			for (int j = 0; j < result.num_attributes; j++)
				temp.insert_cell( j, a.tuples[i].get_cell(j) );
			result.insert_tuple(temp);
		}
		for (int i=0; i < b.tuples.size(); i++){
			Tuple temp(b.attribute_list.num_attributes);
			for (int j=0; j < result.attribute_list.num_attributes; j++)
				temp.insert_cell( j, b.tuples[i].get_cell(j) );
			result.insert_tuple(temp);
		}
        
        delete [] att_names;
        delete [] att_max_lengths;
		return result;	
	}
	else{
        delete [] att_names;
        delete [] att_max_lengths;
		cout<<"These relations are not union compatible\n";
	}
}

Relation Database::set_difference(string name, Relation a, Relation b){
    string att_names* = new string[a.attribute_list.num_attributes];
    int att_max_lengths* = new int[a.attribute_list.num_attributes];
    
    for (int i = 0; i < a.attribute_list.num_attributes; i++){
        att_names[i] = a.attribute_list.attributes[i].get_name();
        att_max_lengths[i] = a.attribute_list.attributes[i].get_max_length();
    }

	if( union_compatible(a, b)){
		int j;
		Relation result( name, att_names, att_max_lengths, a.primary_keys);
		Tuple temp(a.attribute_list.num_attributes);
		for (int i=0; i<a.tuples.size(); i++){
			for(j=0; j<b.tuples.size(); j++){ 
				if (a.tuples[i] == b.tuples[j])
		 			break;
			}
			if(a.tuples[i] != b.tuples[j]){
				temp.cells = a[i].cells;
				result.insert_tuple(temp);
			}
		}
		return result;			
	}
	else{
		cout<<"These relations are not union-compatible, therefore I cannot compute the set difference\n";
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
		Relation result(name, combine_names(a.attribute_list, b.attribute_list), combine_max(a.attribute_list, b.attribute_list), a.primary_keys+b.primary_keys);
		Tuple temp (a.get_num_attributes()+ b.get_num_attributes());
		for (int i=0; i<a.get_num_attributes(); i++){
			for (int j=0; j<b.get_num_attributes(); j++){
				for (int k=0; k<temp.num_attributes(); k++){
					if (k<a.get_num_attributes())
						temp.insert_cell(k, a.tuples[i].get_cell(k));
					else
						temp.insert_cell(k, b.tuples[j].get_cell(k-a.get_num_attributes()));
				}		
				result.insert_tuple( temp);
			}
		}
		return result;
	}
	else{
		cerr<"These relations are not compatible for using the cross product function. Rename the attributes in one of the relations.";
	}
}
	
Relation Database::select(vector<string> att_names, vector<string> compare_values, vector<string> compare_operators, Relation &in_rel, string and_or_gate){
	new Relation(out_rel, att_names, in_rel.get_max(), in_rel.get_primary());
	//Update parameters
	out_rel.set_primary(in_rel.primary_keys, &in_rel);
	out_rel.set_max(in_rel.get_max(), &in_rel);
	vector<int> tuple_indexes;
	if(att_names.size()!= compare_values.size()){	//Check input lengths
		printf ("The number of attribute and compare strings did not match.");
		return null;
	}
	for(int n=0; n<att_names.size();n++){
		if(in_rel.attribute_exist(att_names[n])){
			for(int i=0; i < in_rel.num_attributes; i++){
				if (in_rel.get_attribute_name(i) == att_names[n]){
					if (in_rel.compare(tuple_indexes, compare_values[n], compare_operators[n], i)){//tuple_indexes
						i=in_rel.num_attributes;//saves time
					}
				}
			}
		}
		else{
			printf ("%s attribute was not found.", att_names[n]);
		}
	}
	vector<int> used;

	for(int i=0; i<tuple_indexes.size();i++){
		if(std::count(used.begin(),used_names.end(), tuple_indexes[i])==0){//NO DUPLICATE ATTRIBUTES
			if(and_or_gate[i] == "and"){
			if(std::count(tuple_indexes.begin(), tuple_indexes.end(), tuple_indexes[i]) == att_names.size()){
				out_rel.insert_tuple((in_rel.tuples[i]);
			}
			}else if (and_or_gate[i] == "or"){
				out_rel.insert_tuple((in_rel.tuples[i]);
			}
			used.push_back(tuple_indexes[i])
		}
	}
	
	return out_rel;
}

Relation Database::project(vector<string> att_names, Relation &in_rel){
	Relation out_rel((in_rel.name + "_Projection"), att_names,in_rel.get_max(), in_rel.primary_keys);

	out_rel.set_primary(in_rel.primary_keys, &in_rel);
	out_rel.set_max(in_rel.get_max(), &in_rel);

	for(int i=0; i < att_names.size(); i++){
		if(in_rel.attribute_exist(att_names[i])){
			//add Attributes to out_rel
			out_rel.insert_attribute( in_rel.get_attribute_index(att_names[i]), &in_rel);
		}
		else{
			printf ("%s attribute was not found.", att_names[i]);
		}
	}
	return out_rel;
}

Relation Database::renaming(String out_name, vector<string> att_renames , Relation &in_rel){\
	//correct number of input?
	Relation out_rel(out_name, att_names,in_rel.get_max(), in_rel.primary_keys);
	if(in_rel.num_attributes != att_renames.size()){
		printf ("There was not enough Attributes given or in the Relation.");
	}
	else{
		out_rel.set_tuples_vector(show_relation(in_rel)); //copy table
		out_rel.set_primary(in_rel.primary_keys, &in_rel);
		for(int i=0; i < in_rel.num_attributes; i++){
			out_rel.rename_attribute(att_renames[i],i);
		}
	}
	return out_rel;
}