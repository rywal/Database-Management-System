//
//  Database.cpp
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Database.h"

Database::Database(string _name){
    name = _name;
}


Relation& Database::get_relation(string name) {
   while(name.back()==')'){name.erase(name.size()-1, 1);}
   for (int i = 0; i < relations.size(); i++){
		if(relations[i].name == name){
		   return relations[i];
		}
	}
}

Relation& Database::get_relation(int index) {
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
void Database::create_relation(string name, Relation a){
	vector<string> att_names = a.attribute_list.names();
    vector<int> att_lengths = a.attribute_list.maxes();
	Relation new_relation(name,att_names, att_lengths, a.primary_keys);
	new_relation.tuples=a.tuples;
	relations.push_back(new_relation);

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
		
		if (b.get_size()==0) return a;
		if (a.get_size()==0) return b;
		for (int i=0; i<a.tuples.size(); i++){
			for(j=0; j<b.tuples.size(); j++){ 
				if (a.tuples[i] == b.tuples[j]){
					break;
				}
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
			if(a.get_attribute_name(i)==b.get_attribute_name(j)){
				cout<<a.get_attribute_name(i)<<" : "<<b.get_attribute_name(j)<<endl;
				return false;
			}
		}
	}
	return true;
}

Relation Database::cross_product(string name, Relation a, Relation b){
	if (cross_compatible(a,b)){
        vector<string> prim_keys = a.primary_keys;
        prim_keys.insert( prim_keys.end(), b.primary_keys.begin(), b.primary_keys.end() );
		Relation result(name, a.attribute_list.combine_names(a.attribute_list, b.attribute_list), a.attribute_list.combine_max(a.attribute_list, b.attribute_list), prim_keys);
		for (int i=0; i<a.tuples.size(); i++){
			for (int j=0; j<b.tuples.size(); j++){
            Tuple temp (a.get_num_attributes() + b.get_num_attributes());
				for (int k=0; k<temp.num_attributes(); k++){
                    if (k<a.get_num_attributes()){
						temp.insert_value(k, a.tuples[i].get_cell(k).get_data(), a.tuples[i].get_cell(k).get_max_length());
                    } else {
                        temp.insert_value(k, b.tuples[j].get_cell(k-a.get_num_attributes()).get_data(), b.tuples[j].get_cell(k-a.get_num_attributes()).get_max_length());
                    }
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

Relation Database::select_att( string att_name, string compare_att, string compare_operator, Relation in_rel ){
	Relation out_rel(in_rel.name, in_rel.attribute_list.names(), in_rel.attribute_list.maxes(), in_rel.primary_keys);
	int index1=in_rel.get_attribute_index(att_name);
	int index2=in_rel.get_attribute_index(compare_att);
	vector<int> matching_tuples;

	for (int i=0; i<in_rel.get_size(); i++){
		if(in_rel.compare(in_rel.tuples[i].cells[index1].get_data(), compare_operator, in_rel.tuples[i].cells[index2].get_data() ))
			out_rel.insert_tuple(in_rel.tuples[i]);
	}
	return out_rel;
}

Relation Database::select( string att_name, string compare_value, string compare_operator, Relation in_rel ){
    
    if (in_rel.attribute_exist(compare_value))
    	return select_att(att_name, compare_value, compare_operator, in_rel);
    
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

Relation Database::project(vector<string> att_names, Relation in_rel){
	vector<int> max_lengths;
    for (int a = 0; a < att_names.size(); a++) {
        max_lengths.push_back( in_rel.attribute_list.attributes[ in_rel.get_attribute_index( att_names[a] ) ].get_max_length() );
    }
    
	Relation out_rel((in_rel.name + "_Projection"), att_names, max_lengths, in_rel.primary_keys);
    
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
    for(int i = 0; i < in_rel.tuples.size(); i++){
        vector<string> values;
        for(int col = 0; col < att_names.size(); col++){
            values.push_back( in_rel.tuples[i].cells[in_rel.get_attribute_index(att_names[col])].get_data() );
        }
        out_rel.insert_tuple(values);
    }
    
	return out_rel;
}

Relation Database::renaming(string out_name, vector<string> att_renames , Relation in_rel){
	Relation out_rel(out_name, att_renames, in_rel.get_max(), in_rel.primary_keys);
	if(in_rel.attribute_list.num_attributes() != att_renames.size()){
		printf ("There was not enough Attributes given or in the Relation.");
	}
	else{
		out_rel.set_tuples_vector(in_rel.tuples); //copy table
		
		vector<string> out_keys=in_rel.primary_keys;
		
		for(int i=0; i < in_rel.attribute_list.num_attributes(); i++){
			for(int a=0; a<in_rel.primary_keys.size();a++){
				if(in_rel.get_attribute_name(i)==in_rel.primary_keys[i]){
					out_keys[a]=att_renames[i];//This keeps the same Attribute indexs as the primary keys
				}//That is, after the renaming of them
			}
			out_rel.rename_attribute(att_renames[i],i);
		}
		out_rel.set_primary(out_keys);
	}
	return out_rel;
}
void Database::update(Relation &in_rel, string att_name, string compare_operator, string comparison_value, string update_name, string compare_att){
	vector<int> tuple_indexes;
    in_rel.compare(tuple_indexes,comparison_value,compare_operator,in_rel.get_attribute_index(compare_att/*att_name*/));
    for(int n = 0; n < tuple_indexes.size(); n++){
//            std::cout << "Updating to a new value " << update_name[i] << "\n";
        in_rel.tuples[n].cells[in_rel.get_attribute_index(att_name)].set_value(update_name);
    }
    tuple_indexes.clear();
}

void Database::update(Relation &in_rel,vector<string> att_name, vector<string> update_name, Relation rel_update){
	for(int i=0; i<in_rel.get_size(); i++){
		for(int j=0; j<rel_update.get_size(); j++){
			if(in_rel.tuples[i]==rel_update.tuples[j]){
				for(int k=0; k<att_name.size(); k++)
					in_rel.tuples[i].cells[in_rel.get_attribute_index(att_name[k])].set_value(update_name[k]);
				break;
			}
		}
	}
	
}

std::vector<string> Database::outputRelation(int index) {
    std::vector<string> output;
    string line;
    Relation rel = relations[index];
    line = "CREATE TABLE " + rel.name + " (";
    
    // Add attributes to create string
    for(int a = 0; a < rel.attribute_list.attributes.size(); a++){
        if (a != 0)
            line += ", ";
        
        line = line + rel.attribute_list.attributes[a].get_name() + " ";
        if (rel.attribute_list.attributes[a].get_max_length() == 0) {
            line = line + "INTEGER";
        } else {
            int ml = rel.attribute_list.attributes[a].get_max_length();
//            std::cout << "max size for " << rel.attribute_list.attributes[a].get_name() << " is " << ml << "\n";
            line = line + "VARCHAR(";
            line = line + std::to_string(ml);
            line = line + ")";
        }
    }
    
    line += ")";
    
    // Add primary keys to create string
    if(rel.primary_keys.size() > 0) {
        line += " PRIMARY KEY (";
        line += rel.primary_keys[0];
        for(int i=1; i<rel.primary_keys.size(); i++){
            line += ", " + rel.primary_keys[i];
        }
        line += ")";
    }
    
    line += ";";
//    std::cout << "Pushing back: " << line << "\n";
    output.push_back(line);
    
    for(int t = 0; t < rel.tuples.size(); t++){
//        std::cout << "Size: " << rel.tuples.size() << "\n";
        line = "INSERT INTO " + rel.name + " VALUES FROM (";
        
        for(int a = 0; a < rel.attribute_list.attributes.size(); a++){
            if (a != 0)
                line += ", ";
            
            if (rel.attribute_list.attributes[a].get_max_length() != 0)
                line += '"';
            
            line += rel.tuples[t].get_cell(a).get_data();
            
            if (rel.attribute_list.attributes[a].get_max_length() != 0)
                line += '"';
            
        }
        
        line += ");";
        output.push_back(line);
    }
    
    return output;
}

bool Database::save(int index){
//    std::cout << "Index is: " << index << "\n";
    Relation r = relations[index];
    
    ofstream outputFile;
//    std::cout << "Opening " << r.name << ".db\n";
    outputFile.open (r.name + ".db");
    
    std::vector<string> outputLines;
    outputLines = outputRelation(index);
    
    for (auto line : outputLines) {
        if (line.length()) {
            outputFile << line << "\n";
        }
    }
    outputFile.close();
    return true;
}

bool Database::save(string r){
    std::cout << "Saving r " << r << " with index " << get_relation_index(r) << endl;
    return save( get_relation_index(r) );
}

bool Database::close(int index){
    save(index);
    return true;
}

bool Database::close(string r){
    std::cout << "Closing r " << r << " with index " << get_relation_index(r) << endl;
    return close( get_relation_index(r) );
}

void EXIT(){		//This closes out the application
	exit(0);
}

std::vector<Tuple> Database::show(Relation relation_name){
	return relation_name.tuples;
}

int count_up(Relation relation_name){
	int return_val=0;
	for(int a = 0; a < relation_name.attribute_list.attributes.size(); a++){
		if(relation_name.attribute_list.attributes[a].get_max_length() == 0){
			return_val+=10;
		} else{
			return_val+=relation_name.attribute_list.attributes[a].get_max_length();
		}
    }
	if(return_val==0){
		return 5;
	} else{
		return (return_val);
	}
}

void Database::print_relation(Relation relation_name){
	int rel_s = count_up(relation_name);//FORMATING PERPOSES ONLY
	cout<<endl;
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("-=");}
	printf("-=BEGIN=-=");
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("-=");}
	cout<<"-"<<endl;//FORMATTING
	
	printf ("Relation name:%s \n", relation_name.name.c_str());
    std::cout << "Relation size " << relation_name.tuples.size() << std::endl;
	cout<<endl;
	
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("--");}
	printf("Attributes");
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("--");}
	cout<<"-"<<endl;//FORMATTING
	
    for(int a = 0; a < relation_name.attribute_list.attributes.size(); a++){
		if(relation_name.attribute_list.attributes[a].get_max_length() == 0){
			for (int i = 0; i < 10; i++){
				if(i<relation_name.attribute_list.attributes[a].get_name().size()){
					string temp_sav=relation_name.attribute_list.attributes[a].get_name();
					cout<<temp_sav[i];
				} else{
					printf(" ");
				}
			}
		} else for (int i = 0; i < relation_name.attribute_list.attributes[a].get_max_length(); i++){
				if(i<relation_name.attribute_list.attributes[a].get_name().size()){
					string temp_sav=relation_name.attribute_list.attributes[a].get_name();
					cout<<temp_sav[i];
				} else{
					printf(" ");
				}
			}
    }
	
	cout<<endl;
    for(int i = 0; (i-1)<(rel_s/4); i++){printf ("--");}
	printf("---Rows---");
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("--");}
	cout<<"-"<<endl;//FORMATTING

	for(int k = 0; k < relation_name.tuples.size(); k++) {
		for(int i = 0; i < relation_name.tuples[k].num_attributes(); i++){	
			//printf("%-10s", relation_name.tuples[k].get_cell(i).get_data().c_str());
			if(relation_name.attribute_list.attributes[i].get_max_length() == 0){
				for(int a = 0; a<10;a++){
					if(a<relation_name.tuples[k].get_cell(i).get_data().size()){
						string temp_sav=relation_name.tuples[k].get_cell(i).get_data().c_str();
						cout<<temp_sav[a];
					} else{
						printf(" ");
					}
				}
			} else {
				for(int a = 0; a<relation_name.attribute_list.attributes[i].get_max_length();a++){
					if(a<relation_name.tuples[k].get_cell(i).get_data().size()){
						string temp_sav=relation_name.tuples[k].get_cell(i).get_data().c_str();
						cout<<temp_sav[a];
					} else{
						printf(" ");
					}
				}
			}
		}
		printf ("\n");
	}
	
    printf ("\nPrimary Keys: ");
	if(relation_name.primary_keys.size()>0) {
		cout << relation_name.primary_keys[0];
        for(int i=1; i<relation_name.primary_keys.size(); i++){
            cout <<", "<<relation_name.primary_keys[i];
		}
	}
	cout<<endl;
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("-=");}
	printf("-=-END-=-=");
	for(int i = 0; (i-1)<(rel_s/4); i++){printf ("-=");}
	cout<<"-"<<endl<<endl;//FORMATTING
}