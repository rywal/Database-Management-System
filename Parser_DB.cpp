#include parser.h
#include Database.h

is_command(string command){
        //uses ascii to check if the first letter is uppercase
        return (command[0]>65 && command[0]<90)
}

is_query(string command){
        //uses ascii to check if the first letter is lowercase
        return ((command[0]>97 && command[0]<122)||command[0]==95)
}

Relation make_query(Database &d, vector<string> query);

Relation make_rename(Database &d, vector<string> query){
	int i=1;
	vector<string> names
	query[1].erase(0);
	for(int i=1; query[i].back!=')'; i++){
		//get rid of comma
		query[i].pop_back();
 		names.push_back( query[i])
	}
	query[i].pop_back();
	names.push_back(query[i]);
	if (query[i+=1].front=='('){
		query[i].erase(0);
		const_iterator start =command.begin() + i;
		vector<string> _query(start, command.end());
		return d.renaming(" ", names, make_query(_query);
	}
	else
		return d.renaming(" ", names, d.get_relation(query[i]))		

}

void make_command(Database &d, vector<string> command){
//Exit

//Show

//Save

//Open

//Close

//Delete

//Update

//Insert

//Create

}

Relation make_query(Database &d, vector<string> query){
switch (query[0]){
//Renaming
	case "rename":
		make_rename(d, query);
		break;
//Projection
	case "project":
		make_project(d, query);
		break;
//Selection
	case "select":
		make_select(d, query);
		break;
//relation cases
	default:
		switch (query[1])
//Product
			case "*":
				make_product();
				break;
//Difference
			case "-":
				make_difference();
				break;
//Union
			case "+":
				make_union();
				break
}


void Action(Database &d, vector<string> command){
        if(is_command(command[0]))
                make_command(d, command);
        else if(is_query(command[0])){
		const_iterator start =command.begin() + 2;
		vector<string> query(start, command.end());
               d.create_relation(make_query(d, query));
        	d.relations[d.relations.size()-1].rename_relation(command[0]);
	}else //error
}

	
