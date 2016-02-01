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
			for(int i=0; i < in_rel.get_size(); i++){
				if (strcmp(in_rel.get_attribute_name(i), att_names[n]){
					if (in_rel.compare(tuple_indexes, compare_values[n], compare_operators[n], i)){ //EVERYTHING HAPPENS TO THE TUPLE_INDEXES(important!!!)
						i=in_rel.get_size();//saves time
					}
				}
			}
		}
		else{
			printf ("%s attribute was not found.", att_names[n]);
		}
	}
	for(int i=0; i<tuple_indexes.size();i++){
		if()
		
	}
	//Step 6: Return out_rel
	return out_rel;
}

Relation Project(vector<string> att_names, Relation &in_rel, int[] attribute_max_lengths, string[] primary_keys){
	//Step 1: Get Access to Input Table (in_table) and create temp Table
	new Relation(out_rel, att_names,attribute_max_lengths, primary_keys);
	//Step 2: Find Attribute's names (att_names) in Input Table (in_rel)
	for(int i=0; i < att_names.size(); i++){
		if(in_rel.attribute_exist(att_names[i])){
	//Step 3: add Attributes to new Table(out_rel)
			out_rel.insert(att_names[i]);
		}
		else{
			printf ("%s attribute was not found.", att_names[i]);
		}
	}
	//Step 4: Return out_rel
	return out_rel;
}

Relation Renaming(Relation &out_rel, vector<string> att_renames , Relation &in_rel){
	//Step1: Check if there is correct number of input
	if(in_rel.getsize()!=att_renames.size()){
		printf ("There was not enough Attributes.");
	}
	else{
	//Step 2: Make a copy of Input Table (in_rel) and put into Output (out_rel)
		for(int i=0; i < in_rel.getsize(); i++){
			out_rel.insert(in_rel.getatt[i]);
	//Step 3: Rename each attribute one by one
			out_rel.rename_attribute(att_renames[i],i);
		}
	}
}
