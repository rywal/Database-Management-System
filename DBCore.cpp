#include <iostream>

//Query Operations

Relation select(vector<string> att_names, vector<auto> compare_values, vector<string> compare_operators, Relation &in_rel, int[] attribute_max_lengths, string[] primary_keys){
	//create temp Table
	new Relation(out_rel, att_names,attribute_max_lengths, primary_keys);
	vector<int> tuple_indexes;
	//Check input lengths
	if(att_names.size()!= compare_values.size()){
		printf ("The number of attribute and compare strings did not match.");
		return null; //Not sure what to return
	}
	for(int n=0; n<att_names.size();n++){
		if(in_rel.attribute_exist(att_names[n])){
			for(int i=0; i < in_rel.num_attributes; i++){
				if (strcmp(in_rel.get_attribute_name(i), att_names[n]){
					if (in_rel.compare(tuple_indexes, compare_values[n], compare_operators[n], i)){ //EVERYTHING HAPPENS TO THE TUPLE_INDEXES(important!!!)
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
			if(std::count(tuple_indexes.begin(), tuples_indexes.end(), tuples_indexes[i]) == att_names.size()){
				out_rel.insert(in_rel.get_attribute(i));
			}
			used.push_back(tuple_indexes[i])
		}
	}
	
	return out_rel;
}

Relation Project(vector<string> att_names, Relation &in_rel, int[] attribute_max_lengths, string[] primary_keys){
	//create temp Table
	new Relation(out_rel, att_names,attribute_max_lengths, primary_keys);
	//Find Attribute's names
	for(int i=0; i < att_names.size(); i++){
		if(in_rel.attribute_exist(att_names[i])){
	//add Attributes to out_rel
			out_rel.insert( in_rel.get_attribute(in_rel.get_attribute_index(att_names[i])));
		}
		else{
			printf ("%s attribute was not found.", att_names[i]);
		}
	}
	//Return out_rel
	return out_rel;
}

Relation Renaming(String out_rel, vector<string> att_renames , Relation &in_rel, int[] attribute_max_lengths, string[] primary_keys){
	//correct number of input?
	new Relation(out_rel, att_names,attribute_max_lengths, primary_keys);
	
	if(in_rel.num_attributes != att_renames.size()){
		printf ("There was not enough Attributes given or in the Relation.");
	}
	else{
	//Make a copy of in_rel and put into out_rel
		for(int i=0; i < in_rel.num_attributes; i++){
			out_rel.insert(in_rel.get_attribute[i]);
	//Rename each attribute one by one
			out_rel.rename_attribute(att_renames[i],i);
		}
	}
	return out_rel;
}
