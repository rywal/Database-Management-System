#include "Database.h"

bool is_command(string command){
        //uses ascii to check if the first letter is uppercase
        return (command[0]>65 && command[0]<90);
}

bool is_query(string command){
        //uses ascii to check if the first letter is lowercase
        return ((command[0]>97 && command[0]<122)||command[0]==95);
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

void make_exit(){

}

void make_show(Database &d, vector<string> command){
	
	if 

}

void make_save(Database &d, vector<string> command){


}

void make_open(Database &d, vector<string> command){


}

void make_close(Database &d, vector<string> command){


}

void make_delete(Database &d, vector<string> command){


}

void make_update(Database &d, vector<string> command){


}

void make_insert(Database &d, vector<string> command){


}

void make_create(Database &d, vector<string> command){

}

Relation make_select(Database &d, vector<string> query){

}

Relation make_project(Database &d, vector<string> query){

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
		if(Com=="EXIT"){
			d.exit();
		}
//Show
		else if(Com=="SHOW"){
			if(command[1].front()=='('){
				command[1].erase(0);
				vector<string> _query(command.begin() + 1, command.end());
				d.show(make_query(Database &d, query));	
			}
			d.show(d.get_relation(command[1]));
		}
//Save
		else if(Com=="SAVE"){
			d.save(d.get_relation(command[1]));
		}

			
//Open
		else if(Com=="OPEN"){
			d.open(d.get_relation(command[1]));
		}
//Close
		else if(Com=="CLOSE"){
			d.close(d.get_relation(command[1]));
		}
//Delete
		else if(Com=="DELETE"){
			
			delete();
		}

//Update
		else if(Com=="UPDATE"){
			make_update();
}
//Insert
		else if(Com=="INSERT"){
			make_insert();
}
//Create
		else if(Com=="CREATE"){}
			
			make_create();
}

Relation make_query(Database &d, vector<string> query){

string expr = query[0];
//Renaming
	if (expr == "rename")
		return make_rename(d, query);
//Projection
                                               	else if (expr == "project")
		return make_project(d, query);
//Selection
	else if (expr == "select")
		return make_select(d, query);
//relation cases n
	else{
		string expr2=query[1];
//Product
		if (expr2 == "*")
				return make_product( d, query);
//Difference
		else if (expr2	== "-")
				return make_difference( d, query);
//Union
		else if (expr2 == "+")
				return make_union( d, query);

		else return d.get_relation(expr);
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

	
