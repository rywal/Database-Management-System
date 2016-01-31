#include <iostream>

//Query Operations

Relation select(string att_name, string compare_string, Relation &in_rel){
	//Step 1: Get Access to Input Table (in_table) and create temp Table
	Relation out_rel;
	
	//Step 2: Find Attribute's name (att_name) in Input Table (in_rel)
	if(in_rel.doesexist(att_name)){
	
	//Step 3: Compare compare_string to all Domains in the Attribute's name (att_name)
		for(int i=0; i < in_rel.getsize(); i++){
			if (in_rel.compare(att_name, compare_string, i)){
	//Step 4: For all matching Domains, add the whole Tuple to a new Relation (Say, out_rel)
				out_rel.insert(in_rel.getAttIn(att_name, i)/*Retruns TUPLE*/);
			}
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
		if(in_rel.doesexist(att_names[i])){
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
			//att_oldnames[i] 
			out_rel.insert(in_rel.getatt[i]);
		//Step 3: Rename each attribute one by one
			ch_att_name(att_renames[i],i);
		}
	}
}