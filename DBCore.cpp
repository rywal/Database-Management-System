#include <iostream>

//Query Operations

Relation select(vector<string> att_names, vector<auto> compare_values, vector<string> compare_operators, Relation &in_rel, string and_or_gate){
	new Relation(out_rel, att_names, in_rel.get_max(), in_rel.get_primary());
	//Update parameters
	out_rel.set_primary(in_rel.get_primary(), &in_rel);
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
			if(and_or_gate == "and"){
			if(std::count(tuple_indexes.begin(), tuple_indexes.end(), tuple_indexes[i]) == att_names.size()){
				out_rel.insert(in_rel.tuples[i]);
			}
			}else if (and_or_gate == "or"){
				out_rel.insert(in_rel.tuples[i]);
			}
			used.push_back(tuple_indexes[i])
		}
	}
	
	return out_rel;
}

Relation Project(vector<string> att_names, Relation &in_rel){
	new Relation(out_rel, att_names,in_rel.get_max(), in_rel.get_primary());
	
	out_rel.set_primary(in_rel.get_primary(), &in_rel);
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

Relation Renaming(String out_rel, vector<string> att_renames , Relation &in_rel){
	//correct number of input?
	new Relation(out_rel, att_names,in_rel.get_max(), in_rel.get_primary());
	if(in_rel.num_attributes != att_renames.size()){
		printf ("There was not enough Attributes given or in the Relation.");
	}
	else{
		out_rel.set_tuples_vector(in_rel.get_tuples_vector()); //copy table
		out_rel.set_primary(in_rel.get_primary(), &in_rel);
		for(int i=0; i < in_rel.num_attributes; i++){
			out_rel.rename_attribute(att_renames[i],i);
		}
	}
	return out_rel;
}


//UPDATE-command

void update(Relation &in_rel, vector<string> att_names, string compare_operators, vector<auto> comparison_values){
	vector<int> tuple_indexes;
	for(int i=0; i<att_names.size();i++){
		in_rel.compare(tuple_indexes,comparison_values[i],compare_operators[i],in_rel.get_attribute_index(att_names[i]));
		for(int n=0; n<tuple_indexes;n++){
			in_rel.tuples[n].cells[in_rel.get_attribute_index(att_names[i])].set_value(compare_values[i]);
		}
		tuple_indexes.clear();
	}
}