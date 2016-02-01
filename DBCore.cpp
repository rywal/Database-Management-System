#include <iostream>

//Query Operations

Relation select(vector<string> att_names, vector<string> compare_strings, Relation &in_rel){
	//Step 1: Get Access to Input Table (in_table) and create temp Table
	Relation out_rel;
	if(att_names.size()!= compare_strings.size()){
		printf ("The number of attribute and compare strings did not match.");
		return null; //Not sure what to return
	}
	//Step 2: Find Attributes' names (att_names) in Input Table (in_rel)
	for(int n=0; i<att_names.size();n++){
		if(in_rel.attribute_exist(att_names[n])){
	//Step 3: Compare compare_string to all Domains in the Attribute's name (att_name)
			for(int i=0; i < in_rel.getsize(); i++){
				if (in_rel.compare(att_names[n], compare_strings[n], i)){
	//Step 4: For all matching Domains, add the whole Tuple to a new Relation (Say, out_rel)
					out_rel.insert(in_rel.get_attribute(att_names[n], i)/*Retruns TUPLE*/);
				}
			}
		}
		else{
			printf ("%s attribute was not found.", att_names[n]);
		}
	}
	//Step 5: Return out_rel
	return out_rel;
}

Relation Project(vector<string> att_names, Relation &in_rel){
	//Step 1: Get Access to Input Table (in_table) and create temp Table
	Relation out_rel;
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
