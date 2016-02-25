//
//  ryan_parser.cpp
//  
//
//  Created by Ryan Walters on 2/15/16.
//
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "../DBCore/Database.h"

//------GLOBAL-VARIABLE------//
ofstream output;
int error;
//---------------------------//
//simple function to determine if the input is a command or query
bool is_query(string command){
	//check if the first letter is capitalized
	return ((command[0]>96 && command[0]<123)||command[0]==95);
	//TRUE	= query
	//FALSE	= command
}

//declared functions for recursion purposes
Relation interpret_query(Database &db, std::vector<std::string> command);
int file_input(Database &db, FILE *input, string filename, bool is_open);

//which_op takes "==" symbols and outputs something our program can handle
string which_op(string op){
	if(op=="=="){return "eq";}
	if(op=="!="){return "neq";}
	if(op=="<"){return "le";}
	if(op==">"){return "gr";}
	if(op=="<="){return "leq";}
	if(op==">="){return "geq";}
	return "eq"; //Compare should be eq by default
}

//----------------------------------------------------//
//					Query Interpretations
//Select, Rename, Project, Union, Difference, Product
//----------------------------------------------------//

//------------------------------------------------------------------------------//
//  1)	select has three cases described below, the interpret check which case 
// 		and then acts accordingly eith returning a simple select or a 
// 		set_difference or a set_union of two different selects
//-----------------------------------------------------------------------------//
Relation interpret_select(Database &db, std::vector<std::string> query){
    if(query.size()>3){	
	//declare and initialize the arguments for the select function
	string att_name=query[0];
	string compare=query[1];
	string value=query[2];
	int i;
	//three cases:
	//1) '&&' the selection is going to set_difference two conditions
	if( query[3]=="&&"){
		//the select needs the input relation which is after all the conditions
		for(i=3; query[i]=="&&" || query[i]=="||"; i+=4){}
		vector<string> in_rel_query;
		for(int j=i; j<query.size(); j++)
			in_rel_query.push_back(query[j]);
		query.erase(query.begin(), query.begin() + 4);
		vector<string> rest_of_query=query;
	//	db.select( att_name, value, which_op(compare), interpret_select(db, rest_of_query) );
		return db.set_difference( " ", db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), db.set_difference(" ",  db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), interpret_select(db, rest_of_query)));	
	}
	//2) '||' the selection is going to set_union two conditions
	else if( query[3] =="||"){
		//the select needs the input relation which is after all the conditions
		for(i=3; query[i]=="&&" || query[i]=="||"; i+=4){}
		vector<string> in_rel_query;
		for(int j=i; j<query.size(); j++)	//the select needs the input relation which is after all the conditions
			in_rel_query.push_back(query[j]);
		query.erase(query.begin(), query.begin() + 4);
		vector<string> rest_of_query=query;
		return db.set_union( " ", db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), interpret_select(db, rest_of_query));	
	}
	else {
	//3) the selection is at the end of it's conditions
		query.erase(query.begin(), query.begin()+3); 
		std::vector<std::string> rest_of_query = query;
	std::cout << "Selecting " << att_name << " with value " << value << " with operation " << which_op(compare) <<" from "<<rest_of_query[0]<<endl;//Left as FUNCTIONALITY, not debugging specifically
		return db.select(att_name, value, which_op(compare), interpret_query(db, rest_of_query));
	} 
    } else{
		cout<<"Error not enough tokens to parse the select query"<<endl;
		output<<"The SELECT interpreter was not given the correct number of arguments"<<endl;
		error=16;
    }
}
//--------------------------------------------------------------//
//	2) Rename will search through and take all the words that
//		do not match query key words and add them to the string of 
//		new namesfor the attributes in the specified relation
//--------------------------------------------------------------//
Relation interpret_rename(Database &db, std::vector<std::string> query){
	int i;
	vector<string> names;
	//go through the query and fill the vector with the desired attribute names
	for(i=0; i<(query.size()-1); i++){
		//if it hits the relation name or another query break
		if(query[i]!="select" && query[i]!="project" && query[i]!="rename"){
			if((i+4)==query.size()){ //Is Union,Diff, or prod
				if(query[i+2]=="+" || query[i+2]!="-" || query[i+2]!="*"){
					names.push_back(query[i]);//the last name
					break;
				}
				else {break;}
			}
			names.push_back(query[i]);
		} else{break;} //The next thing is an expr not a new att_name
	} //If it doesn't hit a "break;", then it is a relation name
	vector<string> _query(query.begin() + i, query.end());
	return db.renaming(" ", names, interpret_query(db, _query));
}

//--------------------------------------------------------------//
//	3) Project will search through and take all the words that
//		do not match query key words and add them to the string of 
//		names of the attributes in the specified relation
//--------------------------------------------------------------//
Relation interpret_project(Database &db, std::vector<std::string> query){
	int i; 
	vector<string> names; 
	for(i=0; i<(query.size()-1); i++){ 
		if(query[i]!="select" && query[i]!="project" && query[i]!="rename"){ 
			if((i+4)==query.size()){ //Is Union,Diff, or prod
				if(query[i+2]=="+"||query[i+2]=="-"||query[i+2]=="*"){ 
					names.push_back(query[i]);//the last name
					break;
				}
			} 
			names.push_back(query[i]);
		} else{break;} //The next thing is an expr
	} //If it doesn't hit a "break;", then it is a relation name
	
	vector<string> _query(query.begin() + i, query.end());
	
	return db.project(names, interpret_query(db, _query));
}
//-------------------------------------------------------------------------//
//	4,5,6) The following three functions simply apply the appropriate 
//			function to the remaining query and the already stated relation
//-------------------------------------------------------------------------//
Relation interpret_union(Database &db, std::vector<std::string> query){
		string relation_name= query[0];
		//set up the second relation in the union
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.set_union(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));	
}

Relation interpret_difference(Database &db, std::vector<std::string> query){
		string relation_name=query[0];
		//set up the second relation in the difference
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.set_difference(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));
}

Relation interpret_product(Database &db, std::vector<std::string> query){
		string relation_name= query[0];
		//set up the second relation in the product
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.cross_product(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));
}

//------------------------------//
//	Command Interpretations
// CREATE, INSERT, SHOW, UPDATE
//------------------------------//

//--------------------------------------------------------------------------//
//  1)	CREATE takes in as many attributes (and it's length) until it reaches 
//		PRIMARY upon which it takes the remaining words as the Primary keys
//--------------------------------------------------------------------------//
bool interpret_create(Database &db, std::vector<std::string> command) {
    if (command.size() > 5) {
        string relation_name = command[0];
        
        string next_token = command[1];
        bool column_name_just_found = false;
        std::vector<std::string> attribute_names;
        std::vector<int> attribute_sizes;
        std::vector<std::string> primary_keys;
        int i = 1;
        for (i = 1; i < command.size(); i++){
        	//make the primary keys
            if (command[i] == "PRIMARY")
                break;

            if (!column_name_just_found) {
                attribute_names.push_back( command[i] );
                column_name_just_found = true;
            } else { // set up the attributes of the new table
                if (command[i] == "VARCHAR") {
                    i++;
                    std::string::size_type sz;
                    int attribute_size = std::stoi (command[i], &sz);
                    attribute_sizes.push_back( attribute_size );
                } else if(command[i] == "INTEGER") {
                    attribute_sizes.push_back(0);
                }
                column_name_just_found = false;
            }
        }
        if (command[i] == "PRIMARY" && command[i+1] == "KEY") {
            for (i = i+2; i < command.size(); i++){
                primary_keys.push_back( command[i] );
            }
        }
        db.create_relation(relation_name, attribute_names, attribute_sizes, primary_keys);
    } else {
        std::cout << "Not enough tokens given to interpret a create statement" << std::endl;
		output<<"The CREATE interpreter was not given the correct number of arguments"<<endl;
		error=15;
    }
}

//---------------------------------------------------------------------------//
//  2)	INSERT takes a relation name and then determines whether the values 
//		to be inserted are from a different relation or are a string of values
//		the function then interprets this information and calls the appropriate
//		insert function
//---------------------------------------------------------------------------//
bool interpret_insert(Database &db, std::vector<std::string> command) {
    if (command.size() > 4) {
        string relation_name = command[0];
        
        string next_token = command[1];
        bool from_relation = false;
        std::vector<std::string> attribute_values;
        std::vector<int> attribute_sizes;
        std::vector<std::string> primary_keys;
        int i = 1;
        for (i = 1; i < command.size(); i++){
	    	if (command[i] == "RELATION" ){
		 		from_relation=true;
                break;
       		}
       		//If it passes this statment it is a value to make into a tuple
            if (command[i]!= "VALUES" && command[i] != "FROM") {
                attribute_values.push_back( command[i] );
            }  
        }
        //The 'from relation' type of insert needs to be handled differently
        if (from_relation) {
        	command.erase(command.begin(), command.begin() + i +  1);
			vector<string> rest_of_query=command;
			db.get_relation(relation_name).insert_relation(interpret_query(db, rest_of_query));
        }else {
        	db.get_relation(relation_name).insert_tuple(attribute_values);
        }
    } else {
        std::cout << "Not enough tokens given to interpret an insert statement" << std::endl;
		output<<"The INSERT interpreter was not given the correct number of arguments"<<endl;
		error=14;
    }
}

//----------------------------------------------------------------//
//	3) SHOW simply calls print_relation on the relation
//		derived from the rest of the query (whether it be a  
// 		relation name or a query
//----------------------------------------------------------------//
bool interpret_show(Database &db, std::vector<std::string> command){
	if (command.size()>0){
		if(command.size()==1){
		//the relation is a relation-name
			string relation_name=command[0];
			if(db.get_relation_index(relation_name)==(-1)){//If it doesn't exist
				printf("The relation named: %s does not exist.\n", relation_name.c_str());
				output<<"The relation named: "<<relation_name.c_str()<<" does not exist."<<endl;
				error=13;
			} else{//If it exists, print it (or show it to screen)
				db.print_relation(db.get_relation(relation_name));
			}
		}
		//the relation is a different atomic-expr
		else{
			db.print_relation(interpret_query(db, command));
		}
	}else {
          std::cout << "Not enough tokens given to interpret a show statement" << std::endl;
		  output<<"The SHOW interpreter was not given the correct number of arguments"<<endl;
		  error=12;
       }	
}

//----------------------------------------------------------------//
//	3) UPDATE takes in a list of updates and a list of conditions
//		and uses the information to call a select function to make 
//		a relation that update can use in the update function
//----------------------------------------------------------------//
bool interpret_update(Database &db, std::vector<std::string> command, string relation_name){
	//vectors for vital information for updates
	vector<string> names;
	vector<string> compare_values;
	vector<string> literals;
	vector<string> op_v;
	vector<string> compare_atts;
	vector<string> conjunctions;
	int index;
	//UPDATES
	for(index=0; (index+2)<command.size(); index++){
		if( command[index]=="WHERE"){
			index++;
			break;
		}
		names.push_back(command[index]);
		index++;
		if(command[index] != "="){
			cerr<<"Expected an \"=\" after the attribute-name\n";
			output<<"Update Intrepreter was expected an = after attribute-name"<<endl;
			error=11;
		}
		index++;
		literals.push_back(command[index]);
	}
	//CONDITIONS
	command.erase(command.begin(), command.begin() + index);
	vector<string> rest_of_query=command;
	rest_of_query.push_back(relation_name);
	db.print_relation(interpret_select(db, rest_of_query));
	db.update(db.get_relation(relation_name), names, literals, interpret_select(db, rest_of_query));
}	
//----------------------------------//
//	  Branch Selection Process
// 	1) Command	      2)  Query
//----------------------------------//	

//-----------------------------------------------------------------------//
// 1)  Commands
//		-goes throught the first few words of the input and determines 
//		which command interpretation to take while adding error checking;
//-----------------------------------------------------------------------//
void interpret_command(Database &db, std::vector<std::string> command) {	
    if (command[0] == "CREATE") {
        if (command.size() > 2 && command[1] == "TABLE") {
            command.erase (command.begin(), command.begin()+2);
            std::vector<std::string> rest_of_commands = command;
            interpret_create(db, rest_of_commands);
        } else {
            std::cout << "Error parsing your command - either not enough tokens or 'TABLE' not found" << std::endl;
			output<<"CREATE was not given the correct number of arguments"<<endl;
			error=10;
        }
    } else if(command[0] == "INSERT") {
        if (command.size() > 2 && command[1] == "INTO") {
            command.erase (command.begin(), command.begin()+2);
            std::vector<std::string> rest_of_commands = command;
	     interpret_insert(db, rest_of_commands);
        } else {
            std::cout << "Error parsing your command - either not enough tokens or 'INTO' not found" << std::endl;
			output<<"INSERT was not given the correct number of arguments"<<endl;
			error=9;
        }
    } else if(command[0] == "SHOW"){
		if (command.size() > 1){
			command.erase(command.begin(), command.begin()+1); 
			std::vector<std::string> rest_of_commands = command;
			if (rest_of_commands.size()==2){//Doubly insures SHOW
				rest_of_commands.clear();
				rest_of_commands.push_back(command[0]);
			}
			interpret_show(db, rest_of_commands);
		} else {
            std::cout << "Error parsing your command - not enough tokens"<< std::endl;
			output<<"SHOW was not given the correct number of arguments"<<endl;
			error=8;
        }  
    } else if(command[0] == "SAVE"){
    	if (command.size()==2){
    		db.save(command[1]);
    	} else{
    		cout<<"Too many tokens for a SAVE command which can only take the form:\n";
    		cout<<"SAVE \'relation-name\'\n";
			output<<"The format for SAVE was not correct"<<endl;
			error=7;
    	}
    } else if(command[0]=="OPEN"){
		if (command.size()==2){
			string input_w = command[1]+".db";
			string filename = command[1]+".db";
			FILE *input=fopen(input_w.c_str(), "r");
			file_input(db, input,filename,true);
		} else {
			printf("The number of arguments for OPEN is incorrect.\n");
			output<<"OPEN was not given the correct number of arguments."<<endl;
			error=6;
		}
    } else if(command[0]== "CLOSE"){
		if (command.size()==2){
			db.save(command[1]);
			for(int i=0; i< db.relations.size();i++){
				if(db.get_relation(i).name.c_str()==command[1])
					db.relations.erase(db.relations.begin() + i);
			}
		} else {
			printf("The number of arguments for CLOSE is incorrect.\n");
			output<<"CLOSE was not given the correct number of arguments."<<endl;
			error=5;
		}
    } else if(command[0]=="DELETE"){
    	if(command.size()>2 && command[1]=="FROM"){
    		string relation_name= command[2];
    		command.erase(command.begin(), command.begin()+4); 
			std::vector<std::string> rest_of_commands = command;
			rest_of_commands.push_back(relation_name);
			db.delete_tups(db.get_relation(relation_name), interpret_select(db, rest_of_commands));
    	}else{
    		cout<<"Error parsing your command- not enough tokens or FROM was not found"<<endl;
    	}
    } else if(command[0]=="UPDATE"){
		if(command.size()>6 && command[2]=="SET"){
			string relation_name= command[1];
			command.erase(command.begin(), command.begin()+3); 
			std::vector<std::string> rest_of_commands = command;
			interpret_update(db, rest_of_commands, relation_name);
		} else {
			std::cout << "Error parsing your command - not enough tokens or SET was not found"<< std::endl;
			output<<"UPDATE was not given the correct number of arguments."<<endl;
			error=3;
		}
    } else {
        std::cout << "Error parsing your command" << std::endl;
		output<<"There was an error parsing the last command."<<endl;
		error=2;
    }
}

//------------------------
// 2) Queries
//		-goes throught the first few words of the input and determines which query
//		interpretation to take while adding error checking;
//------------------------
Relation interpret_query(Database &db, std::vector<std::string> query){
    if (query[0]=="select"){
		query.erase(query.begin(), query.begin()+1); 
		std::vector<std::string> rest_of_query = query;
		return interpret_select(db, rest_of_query);
    } else if (query[0]=="rename"){
		query.erase(query.begin(), query.begin()+1); 
		std::vector<std::string> rest_of_query = query;
		return interpret_rename(db, rest_of_query);
	} else if (query[0]=="project"){
		query.erase(query.begin(), query.begin()+1); 
		std::vector<std::string> rest_of_query = query;
		return interpret_project(db, rest_of_query);
	} else{
		if(query.size()>2){//Prevent SegFault
		//check for union, difference, and product
			if(query[1]=="+"){
				return interpret_union(db, query);
			} else if(query[1]=="-"){
				return interpret_difference(db, query);
			} else if(query[1]=="*"){
				return interpret_product(db, query);
			}
		}else{
			return	db.get_relation(query[0]);
    	}
    }
}

//-----------------------------------------------------------------------//
// - The following function acts as the first node in the parsing process
// - It determines whether the function is a query or a command and then 
//		sends the command to the proper interpretation course 
//----------------------------------------------------------------------//
void query_or_command(Database &db, std::vector<std::string> command_line){
	if(is_query(command_line[0])){
		string relation_name= command_line[0];
		if(command_line[1]=="<-"){
			command_line.erase (command_line.begin(), command_line.begin()+2);
            std::vector<std::string> rest_of_query = command_line;
			db.create_relation(relation_name, interpret_query(db, rest_of_query));
		} else{
			cout<<"Error parsing your command expected <- after relation-name"<<endl;
			output<<"Query failed. Expecting <- after relation-name"<<endl;
			error=1;
		}
	} else{
		interpret_command(db, command_line);
	}
}

//------------------------------------------------------------------//
//	-file_input takes a file and reads in the commands/queries given
//	-it is particularly used in the open function 
//------------------------------------------------------------------//
int file_input(Database &db, FILE *input, string filename, bool is_open){
	vector<string> command_list;
	char* str;
	char* pch;
	string delimiters = " ,();\n";
	if(!input){
		printf("\nThe file: %s not found!", filename.c_str());
		printf("\nPlease place the input folder as in the same folder as %s.\n\n", __FILE__);
		exit(EXIT_FAILURE);//Showing error status code
	}
	int line_number=1;
	size_t buffer_size=0;
	while(!feof(input)){
		//get a command from the file
		getline(&str, &buffer_size, input); 
		string command(str);
		if(!is_open){
		//prints the command back to the user
			printf("The given command is: %s\n",str);
		}
		//tokenizes the command
		pch = strtok (str, delimiters.c_str());
			while (pch != NULL) {
			//put the token in to a vector to make the command easy to parse
				command_list.push_back(pch);
				pch = strtok (NULL, delimiters.c_str());
		}
//Check for EXIT command
		if(command_list[0]=="EXIT" && command_list.size()==1){//Preventing SegFault
			output<<"-=-=-=-=-EXITED-=-=-=-=-"<<endl;
			exit(0);
		} else{	
		//This marks the beginning of the query/command interpretation
			query_or_command(db, command_list);
		}
		if(!is_open){
			if(error==0){
				//The output file contains all instances of successful commands
				output<<"Line number "<<line_number<<" was successful!"<<endl;
			} else {
				//The output file contains all instances of failed commands
				output<<"Line number "<<line_number<<" FAILED!"<<endl;}
		} else{
			if(error==0){
				output<<"In file "<<filename.c_str()<<", line number "<<line_number<<" was successful!"<<endl;
			} else{
				output<<"In file "<<filename.c_str()<<", line number "<<line_number<<" FAILED!"<<endl;
			}
		}
		//prepare for next command
		command_list.clear();
		free(pch);
		line_number++;
	}
	if(is_open){
		if(error==0){
			printf("%s was successfully opened!\n", filename.c_str());
			output<<"The file "<<filename.c_str()<<" was successfully opened!"<<endl;
		} else{ 
			printf("There were problems opening %s\n", filename.c_str());
			output<<"The file "<<filename.c_str()<<" FAILED to opened correctly!"<<endl;
		}
	} else{
		output<<"-=-=-=-=-=END-=-=-=-=-=-";
	}
	fclose(input);
}

