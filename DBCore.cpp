#include <iostream>

//Query Operations




//UPDATE-command - WHERE TO PUT??
/*
void update(Relation &in_rel, vector<string> att_names, vector<string> compare_operators, vector<string> comparison_values, vector<string> update_name){
	vector<int> tuple_indexes;
	for(int i=0; i<att_names.size();i++){
		in_rel.compare(tuple_indexes,comparison_values[i],compare_operators[i],in_rel.get_attribute_index(att_names[i]));
		for(int n=0; n<tuple_indexes.size();n++){
			in_rel.tuples[n].cells[in_rel.get_attribute_index(att_names[i])].set_value(update_name[i]);
		}
		tuple_indexes.clear();
	}
}*/
