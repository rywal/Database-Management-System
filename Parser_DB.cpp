#include "Database.h"

bool is_command(string command){
        //uses ascii to check if the first letter is uppercase
        return (command[0]>65 && command[0]<90);
}

bool is_query(string command){
        //uses ascii to check if the first letter is lowercase
        return ((command[0]>97 && command[0]<122)||command[0]==95);
}

int which_atomic(Database &d, string atomic, string at2){
	//at2 is the next element, "null"
	if (atomic == "EXIT" || atomic == "CLOSE" || atomic == "SAVE" || atomic == "OPEN" || atomic == "SHOW" || atomic == "CREATE" || atomic == "UPDATE" || atomic == "INSERT" || atomic == "DELETE"){
		return 0; //Command
	} else if (atomic == "select" || atomic == "project" || atomic == "rename" || at2 == "+" || at2 == "-" || at2 == "*"){
		return 1; //Query
	} else{
		return 2; //Relation-Name
	}
}

Relation make_query(Database &d, vector<string> query);

Relation make_product(Database &d, vector<string> query){
	if(query[2].front()=='('){
		query[2].erase(0);
		vector<string> _query(query.begin() + 2, query.end());
		return d.cross_product(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else return d.cross_product(" ", d.get_relation(query[0]), d.get_relation(query[2]));
}

Relation make_difference(Database &d, vector<string> query){
	if(query[2].front()=='('){
		query[2].erase(0);
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_difference(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else return d.set_difference(" ", d.get_relation(query[0]), d.get_relation(query[2]));
}

Relation make_union(Database &d, vector<string> query){
	if(query[2].front()=='('){
		query[2].erase(0);
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_union(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else return d.set_union(" ", d.get_relation(query[0]), d.get_relation(query[2]));
}

Relation make_select(Database &d, vector<string> query){
	query[1].erase(0,1);
	query[query.size()-1].pop_back();
	int atomic_start = 0;
	
	for(int i=0; i < query.size();i++){	
		if(strstr(query[i].c_str(),")")){
				atomic_start=i;
				i=query.size()+1;//"+1" to show exiting for loop
		}
	}
	vector<string> atom(query.begin() + atomic_start, query.end());
		
	d.create_relation(query.back() + "_select", d.get_relation(query.back()).attribute_list.names(), d.get_relation(query.back()).attribute_list.maxes(), d.get_relation(query.back()).primary_keys);
	Relation rel_sel = d.get_relation(query.back() + "_select");
	
	for(int i=1; i < query.size();i++){		
		if(strstr(query[i].c_str(),")")){//end of codition
			query[i].pop_back();
			i=query.size()+1;//"+1" to show exiting for loop
		}
		if(which_atomic(query[atomic_start])== 0){//query
			Relation sel = d.select(query[i],query[i+3], query[i+2], d.create_relation(query.back() + "_atomic", make_query(d, atom)));
		} else if(which_atomic(query[atomic_start])== 1){//command
			Relation sel = d.select(query[i],query[i+3], query[i+2], d.create_relation(query.back() + "_atomic", make_command(d, atom)));
		} else if(which_atomic(query[atomic_start])== 2){//relation name
			Relation sel = d.select(query[i],query[i+3], query[i+2], d.get_relation(query[atomic_start]);
		}
		if((i+4)>=query.size()){ //Preventing Seg_fault
			if(query[i+4] == "&&"){
				Relation rel_sel = d.set_union(query.back() + "_union" + std::to_string(i), rel_sel, sel);
			}else if(query[i+4] == "||"){
				Relation rel_sel = d.set_difference(query.back() + "_differce" + std::to_string(i), rel_sel, sel);
			}
		}
	}
	return rel_sel;
}

Relation make_project(Database &d, vector<string> query){
	int i;
	vector<string> names;
	query[1].erase(0);
	for(i=1; query[i].back()!=')'; i++){
		//get rid of comma
		query[i].pop_back();
 		names.push_back( query[i]);
	}
	query[i].pop_back();
	names.push_back(query[i]);
	if (query[i+=1].front()=='('){
		query[i].erase(0);
		vector<string> _query(query.begin() + i, query.end());
		return d.project(names, make_query(d, _query));
	}
	else
		return d.project(names, d.get_relation(query[i]));	
}

Relation make_rename(Database &d, vector<string> query){
	int i;
	vector<string> names;
	query[1].erase(0);
	for(i=1; query[i].back()!=')'; i++){
		//get rid of comma
		query[i].pop_back();
 		names.push_back( query[i]);
	}
	query[i].pop_back();
	names.push_back(query[i]);
	if (query[i+=1].front()=='('){
		query[i].erase(0);
		vector<string> _query(query.begin() + i, query.end());
		return d.renaming(" ", names, make_query(d, _query));
	}
	else
		return d.renaming(" ", names, d.get_relation(query[i]));		

}

void make_command(Database &d, vector<string> command){
	string Com =command[0];
//Exit
		if(Com=="EXIT"){}
	//		make_exit();
//Show
		else if(Com=="SHOW"){}
	//		make_show();
//Save
		else if(Com=="SAVE"){}
	//		make_save();
//Open
		else if(Com=="OPEN"){}
	//		make_open();
//Close
		else if(Com=="CLOSE"){}
	//		make_close();
//Delete
		else if(Com=="DELETE"){}
	//		make_delete();
//Update
		else if(Com=="UPDATE"){}
	//		make_update();
//Insert
		else if(Com=="INSERT"){}
	//		make_insert();
//Create
		else if(Com=="CREATE"){}
	//		make_create();
}

Relation make_query(Database &d, vector<string> query){

string expr = query[0];
//Renaming
	if (expr == "rename")
		make_rename(d, query);
//Projection
	else if (expr == "project")
		make_project(d, query);
//Selection
	else if (expr == "select")
		make_select(d, query);
//relation cases
	else{
		string expr2=query[1];
//Product
		if (expr2 == "*")
				make_product( d, query);
//Difference
		else if (expr2	== "-")
				make_difference( d, query);
//Union
		else if (expr2 == "+")
				make_union( d, query);
	}
}


void Action(Database &d, vector<string> command){
        command[command.size()-1].pop_back();
	if(is_command(command[0]))
                make_command(d, command);
        else if(is_query(command[0])){
		vector<string> query(command.begin() + 2, command.end());
               d.create_relation(command[0], make_query(d, query));
	}else {}//error
}

int main(){

}

	
