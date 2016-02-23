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
bool is_query(string command){
	return ((command[0]>96 && command[0]<123)||command[0]==95);
}
Relation interpret_query(Database &db, std::vector<std::string> command);
int file_input(Database &db, FILE *input, string filename);

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

Relation interpret_select(Database &db, std::vector<std::string> query){
    if(query.size()>3){	
	//declareand initialize the arguments for the select function
	string att_name=query[0];
	string compare=query[1];
	string value=query[2];
	int i;
	//three cases:
	//1) the selection is going to set_difference two conditions
	if( query[3]=="&&"){
		for(i=3; query[i]=="&&" || query[i]=="||"; i+=4){}
		vector<string> in_rel_query;
		for(int j=i; j<query.size(); j++)
			in_rel_query.push_back(query[j]);
		query.erase(query.begin(), query.begin() + 4);
		vector<string> rest_of_query=query;
	//	db.select( att_name, value, which_op(compare), interpret_select(db, rest_of_query) );
		return db.set_difference( " ", db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), db.set_difference(" ",  db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), interpret_select(db, rest_of_query)));	
	}
	//2) the selection is going to set_union two conditions
	else if( query[3] =="||"){
		for(i=3; query[i]=="&&" || query[i]=="||"; i+=4){}
		vector<string> in_rel_query;
		for(int j=i; j<query.size(); j++)
			in_rel_query.push_back(query[j]);
		query.erase(query.begin(), query.begin() + 4);
		vector<string> rest_of_query=query;
		return db.set_union( " ", db.select(att_name, value, which_op(compare), interpret_query(db, in_rel_query) ), interpret_select(db, rest_of_query));	
	}
	else {
	//3) the selection is at the end of it's conditions
		query.erase(query.begin(), query.begin()+3); 
		std::vector<std::string> rest_of_query = query;
	std::cout << "Selecting " << att_name << " with value " << value << " with operation " << which_op(compare) <<" from "<<rest_of_query[0]<<endl;
		return db.select(att_name, value, which_op(compare), interpret_query(db, rest_of_query));
	} 
    } else{
	cout<<"Error not enough tokens to parse the select query"<<endl;
    }
}

Relation interpret_rename(Database &db, std::vector<std::string> query){
	int i;
	vector<string> names;
	for(i=0; i<(query.size()-1); i++){
		if(query[i]!="select"&&query[i]!="project"&&query[i]!="rename"){
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
	return db.renaming(" ", names, interpret_query(db, _query));
}

Relation interpret_project(Database &db, std::vector<std::string> query){
	int i; 
	vector<string> names; 
	for(i=0; i<(query.size()-1); i++){ 
		if(query[i]!="select"&&query[i]!="project"&&query[i]!="rename"){ 
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

Relation interpret_union(Database &db, std::vector<std::string> query){
		string relation_name= query[0];
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.set_union(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));	
}

Relation interpret_difference(Database &db, std::vector<std::string> query){
		string relation_name=query[0];
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.set_difference(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));
}

Relation interpret_product(Database &db, std::vector<std::string> query){
		string relation_name= query[0];
		query.erase(query.begin(), query.begin() + 2);
		vector<string> rest_of_query=query;
		return db.cross_product(" ", db.get_relation(relation_name), interpret_query(db, rest_of_query));
}

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
            if (command[i] == "PRIMARY")
                break;
            
            if (!column_name_just_found) {
                attribute_names.push_back( command[i] );
     //           std::cout << "Attribute found with name: " << command[i];
                column_name_just_found = true;
            } else {
                if (command[i] == "VARCHAR") {
                    i++;
                    std::string::size_type sz;
                    int attribute_size = std::stoi (command[i], &sz);
                    attribute_sizes.push_back( attribute_size );
         //           std::cout << " Inserting with size: " << attribute_size << std::endl;
                } else if(command[i] == "INTEGER") {
                    attribute_sizes.push_back(0);
           //         std::cout << " Inserting with size: 0" << std::endl;
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
    }
}

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

            if (command[i]!= "VALUES" && command[i] != "FROM") {
                attribute_values.push_back( command[i] );
           //     std::cout << "Attribute found with name: " << command[i]<<endl;
            }  
        }
        
        if (from_relation) {
        	command.erase(command.begin(), command.begin() + i +  1);
			vector<string> rest_of_query=command;
			db.get_relation(relation_name).insert_relation(interpret_query(db, rest_of_query));
        }else {
        	db.get_relation(relation_name).insert_tuple(attribute_values);
        }
    } else {
        std::cout << "Not enough tokens given to interpret an insert statement" << std::endl;
    }
}

bool interpret_show(Database &db, std::vector<std::string> command){
	if (command.size()>0){
		if(command.size()==1){
			string relation_name=command[0];
			db.print_relation(db.get_relation(relation_name));
		}
		else{
			db.print_relation(interpret_query(db, command));
		}		
	}else {
          std::cout << "Not enough tokens given to interpret a show statement" << std::endl;
       }	
}
bool interpret_update(Database &db, std::vector<std::string> command, string relation_name){
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
	/*for(index; (index+3)<command.size(); index++){
		compare_atts.push_back(command[index]);
		index++;
		op_v.push_back(command[index]);
		index++;
		compare_values.push_back(command[index]);
		index++;
		if (command[index]=="&&" || command[index]=="||" )
			conjunctions.push_back()
	}
		compare_atts.push_back(command[index]);
		index++;
		op_v.push_back(command[index]);
		index++;
		compare_values.push_back(command[index]);
		index++;
			
	for(int i=0; i<names.size(); i++){
		
		cout<<"updating: "<<names[i]<<" : "<<op_v[i]<<" : "<<compare_values[i]<< " : "<<literals[i]<<" : "<<compare_atts[i]<<endl;
		db.update(db.get_relation(relation_name), names[i], op_v[i], compare_values[i], literals[i], compare_atts[i]);
	}*/
}	
			
void interpret_command(Database &db, std::vector<std::string> command) {	
    if (command[0] == "CREATE") {
        if (command.size() > 2 && command[1] == "TABLE") {
            command.erase (command.begin(), command.begin()+2);
            std::vector<std::string> rest_of_commands = command;
            interpret_create(db, rest_of_commands);
        } else {
            std::cout << "Error parsing your command - either not enough tokens or 'TABLE' not found" << std::endl;
        }
        
    } else if(command[0] == "INSERT") {
        if (command.size() > 2 && command[1] == "INTO") {
            command.erase (command.begin(), command.begin()+2);
            std::vector<std::string> rest_of_commands = command;
	     interpret_insert(db, rest_of_commands);
        } else {
            std::cout << "Error parsing your command - either not enough tokens or 'INTO' not found" << std::endl;
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
        }  
    } else if(command[0] == "SAVE"){
    	if (command.size()==2){
    		db.save(command[1]);
    	} else{
    		cout<<"Too many tokens for a SAVE command which can only take the form:\n";
    		cout<<"SAVE \'relation-name\'\n";
    	}
    } else if(command[0]=="OPEN"){
		string input_w = command[1]+".db";
		string filename = command[1]+".db";
		FILE *input=fopen(input_w.c_str(), "r");
		file_input(db, input,filename);
    } else if(command[0]== "CLOSE"){
    
    } else if(command[0]=="DELETE"){
    
    } else if(command[0]=="UPDATE"){
		if(command.size()>6 && command[2]=="SET"){
			string relation_name= command[1];
			command.erase(command.begin(), command.begin()+3); 
			std::vector<std::string> rest_of_commands = command;
			interpret_update(db, rest_of_commands, relation_name);
		} else {
			std::cout << "Error parsing your command - not enough tokens or SET was not found"<< std::endl;
		}
    } else {
        std::cout << "Error parsing your command" << std::endl;
    }
}
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

void query_or_command(Database &db, std::vector<std::string> command_line){
	if(is_query(command_line[0])){
		string relation_name= command_line[0];
		if(command_line[1]=="<-"){
			command_line.erase (command_line.begin(), command_line.begin()+2);
            std::vector<std::string> rest_of_query = command_line;
			db.create_relation(relation_name, interpret_query(db, rest_of_query));
	//		cout<<"just created relation with the name: "<<relation_name<<endl;
		} else{
			cout<<"Error parsing your command expected <- after relation-name"<<endl;	}
	} else{
		interpret_command(db, command_line);
	}
}

int file_input(Database &db, FILE *input, string filename){
	vector<string> command_list;
	char* str;
	char* pch;
	string delimiters = " ,();\n";
	if(!input){
		printf("\nThe input file not found!");
		printf("\nPlease place a file named \"Input.txt\" in the same folder as %s.\n\n", __FILE__);
		exit(EXIT_FAILURE);//Showing error status code
	}
	int line_number=1;
	size_t buffer_size=0;
	while(!feof(input)){
		getline(&str, &buffer_size, input); 
		string command(str);
		cout<< "The following is the command given: " << str << endl;
		pch = strtok (str, delimiters.c_str());
			while (pch != NULL) {
				command_list.push_back(pch);
				pch = strtok (NULL, delimiters.c_str());
		}
		if(command_list[0]=="EXIT" && command_list.size()==1){//Preventing SegFault
			exit(0);
		} else{query_or_command(db, command_list);}
		command_list.clear();
		free(pch);
	}
	fclose(input);
}

int main() {
 	ofstream output;
	output.open ("Output.txt");
	Database db("db");
	char* str;
	char* pch;
	int i=0;
	size_t buffer_size=0;
	string delimiters = " ,();\n";
	vector<string> command_list;	
	if(!output){ //This should never happen
		printf("\nThe Output file is not found!");
		exit(EXIT_FAILURE);//Showing error status code
	}
	string f_or_h;
	printf("For this run, would you like to take input from an \"Input.txt\" file [f], or type commands in by hand[h]?\n(If your input has a \".txt\" in it, it'll be processes as a file)\n>");//Giving better testing handles
	cin >>  f_or_h;
	int loop=1;
	while (loop==1){
		if(f_or_h != "h" && f_or_h != "H" && f_or_h != "hand" && f_or_h != "f" && f_or_h != "F" && f_or_h != "file" && !strstr(f_or_h.c_str(),".txt")){
		//	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		//	f_or_h = "";
			printf("Please re-enter your prefered input method [f\\h]\n>");
			cin >>  f_or_h;
		} else{loop=0;}
	}
	if(f_or_h == "f" || f_or_h == "F" || f_or_h == "file" || strstr(f_or_h.c_str(),".txt")){
		char* input_file;
		FILE *input;
		string filename;
		//input_file="input.txt"; 
		if(strstr(f_or_h.c_str(),".txt")){
			string input_w = "Parser/" + f_or_h;
			filename = "Parser/" + f_or_h;
			input=fopen(input_w.c_str(), "r");
		}else{
			printf("Please input the file you would like to use. \n(Please note, this is automated, no other input will be read)\n>");
			getline(&input_file, &buffer_size, stdin);
			filename = "input.txt";
			input= fopen("input.txt", "r");
		}
		file_input(db, input, filename);//Where the action happens
	} else if (f_or_h == "h" || f_or_h == "H" || f_or_h == "hand"){
		/*int line_number=1;
		std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		while(1){ 
			string command;
			printf("Please enter a command:\n");
			std::getline (std::cin,command);
			cout<<"1\n";
			stringstream ss(command);
			cout<<command<<'\n';
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> command_list(begin, end);
			main_loop(command_list, command, line_number,d);
		}*/
	}
	output.close();
	
    //db.print_relation( db.get_relation("dogs") );
    return 0;
}