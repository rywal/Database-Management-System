//
//  Database.cpp
//
#include "Database.h"

Database::Database(string name){
    
}

void Database::create_relation(string name, string[] attribute_names, int[] attribute_types, string[] primary_keys){
    Relation new_relation = Relation(name, attribute_names, attribute_types, primary_keys);
    relations.push_back(new_relation);
}

bool Database:: union_compatible(Relation a, Relation b){
	
	if(a.get_num_attributes()==b.get_num_attributes()){
		for(int i=0; i<a.get_num_attributes(); i++){
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
		Relation result( name, a.att_names, a.att_max_lengths, a.prim_keys);
		for (int i=0; i<a.tuples.size(); i++){
			Tuple temp(a.num_attributes);
			for (int j=0; j<result.num_attributes; j++)
				temp.cells[j]=a.tuple[i].cells[j];
			result.insert_tuple(temp);
		}
		for (int i=0; i<b.tuples.size(); i++){
			Tuple temp(b.num_attributes);
			for (int j=0; j<result.num_attributes; j++)
				temp.cells[j]=b.tuple[i].cells[j];
			result.insert_tuple(temp);
		}	
	}
	else{
		cout<<"These relations are not union compatible\n";
	}
	return result;
}

Relation Database:: set_difference(string name, Relation a, Relation b){

	if( union_compatible(a, b)){
		int j;
		Relation result( name, a.att_names, a.att_max_lengths, a.prim_keys);
		Tuple temp(a.num_attributes);
		for (int i=0; i<a.tuples.size(); i++){
			for(j=0; j<b.tuples.size(); j++){ 
				if (a.tuples[i]==b.tuples[j])
		 			break;
			}
			if(a.tuples[i]!=b.tuples[j]){ 	
				temp.cells=a[i].cells;
				result.insert_tuple(temp);
			}
		}			
	}
	else{
		cout<<"These relations are not union-compatible, therefore I cannot compute the set difference\n";
	}
	return result;
}

bool Database:: cross_compatible(Relation a,Relation b){
	
	for(int i=0; i<a.get_num_attributes(); i++){
		for( int j=0; j<b.get_num_attributes(); j++){
			if(a.get_attribute_name(i)==b.get_attribute_name(j))
				return false;
		}
	}
	return true;
}

Relation Database:: cross_product(string name, Relation a, Relation b){

	if (cross_compatible(a,b)){
		Relation result(name, combine_names(a.attribute_list, b.attribute_list), combine_max(a.attribute_list, b.attribute_list), a.get_primary()+b.get_primary());
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
	}
	else{
		cerr<"These relations are not compatible for using the cross product function. Rename the attributes in one of the relations.";
	}
}
		

	






