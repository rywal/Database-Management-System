//
//  Database.cpp
//
#include "Database.h"

bool Database:: union_compatible(Relation a, Relation b){
	
	if(a.num_attributes==b.num_attributes){
		for(int i=0; i<a.num_attributes; i++){
			if(a.attribute_names[i]!=b.attribute_names[i])
				return false;
			}
		return true;
	else return false;
	

void Database:: new_relation(Relation newr){		//will push a new relation onto the vector 'relations'
	
	relations.push_back(newr);
	return;
}

Relation Database:: set_union(string name, Relation a, Relation b){

	if (union_compatible(a, b)){
		Relation result( name, a.att_names, a.att_max_length, a.prim_keys)
		Tuple 
	}
	else{
		cout<<"These relations are not union compatible\n";
	}
	return;
}

Relation Database:: set_difference(string name, Relation a, Relation b){

	if( union_compatible(a, b)){

		//difference

	}
	else{
		cout<<"These relations are not union-compatible, therefore I cannot compute the set difference\n";
	}
	return;
}