#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <boost/algorithm/string.hpp>


using namespace std;

//Global Variable - Output file
ofstream output_test;
//Global Variable

bool contains_condition(vector<string> &command_list, int &index);
bool is_selection(vector<string> &command_list, int &index);
bool is_renaming(vector<string> &command_list, int &index);
bool is_atomic(vector<string> &command_list, int &index);
bool is_expr(vector<string> &command_list, int &index);

bool is_operator(string op){//Tests operator
	if(op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">="){
		return true;
	}else{
		//printf("%s is not a valid operator", op.c_str());
		output_test<<"The string "<<op.c_str()<<" is not a valid operator"<<endl;
		return false;
	}
}

bool contains_operand_combo(vector<string> &command_list, int &index){
	if((command_list.size() - index)>3){//this checks if the operator combo is correct
		if(!strstr(command_list[index].c_str(),")") && !strstr(command_list[index].c_str(),"(") && !strstr(command_list[index+1].c_str(),")")&&!strstr(command_list[index+1].c_str(),"(")&&!strstr(command_list[index+2].c_str(),"(")){
			if (is_operator(command_list[index+1])){
				index += 3;
				return true;
			}
		}else{
			//printf("The amount of parentheses given for an operator combo is incorrect.\n");
			output_test<<"The operator combo's parenthese is incorrect"<<endl;
			return false;
		}
	}else{return false;}
	//printf("There was an unknown error in operator combo.\nPlease re-compile this and re-run command.\n\n");
	output_test<<"Unknown error in operator combo"<<endl;
	return false;
}


bool contains_comparison(vector<string> &command_list, int &index){ //This asks if the pattern is correct for a comparision
	for (int i = index; i < command_list.size();i++){
		if (!contains_operand_combo(command_list, i)){
			if(strstr(command_list[i].c_str(),"(")){
				command_list[i].erase(0,1);
				if(strstr(command_list[i].c_str(),"(")){
					//printf("The parentheses for a comparison was not in the front of the word.\n");
					output_test<<"Parentheses for a comparison is not in front of a word"<<endl;
					return false;
				} else if(!contains_condition(command_list, i)){
					return false;
				}	
			}else{return false;}
		}
		index=i;
	}
	return true;
}

bool contains_conjunction(vector<string> &command_list, int &index){//This asks if the pattern is correct for a conjunction
	int temp = index;
	if(contains_comparison(command_list,index)){
		for (int i = index; i < command_list.size();i++){
			if (i>temp){
				if(!strstr(command_list[i].c_str(),"&&")){return false;}
			}
			i+=1;
			if(!contains_comparison(command_list, i)){
				return false;
			}
			index=i;
		}
	}
	return true;
}

bool contains_condition(vector<string> &command_list, int &index){ //This asks if the pattern is correct for a condition
	int temp = index;
	if(contains_conjunction(command_list,index)){
		for (int i = index; i < command_list.size();i++){
			if(i>temp){
				if(!strstr(command_list[i].c_str(),"||")){
					//printf("The || operator is needed inbetween conjunctions.\n");
					output_test<<"The || operator is needed inbetween conjunctions."<<endl;
					return false;
				}
			}
			i+=1;
			if(!contains_conjunction(command_list, i)){
				//printf("The argument provided for a condition is unknown.\n");
				output_test<<"The argument provided for a condition is unknown."<<endl;
				return false;
			}
			index=i;
		}
	}
	return true;
}

bool is_selection(vector<string> &command_list, int &index){ //This asks if the statement is a selection
	if(command_list[index] == "select"){
		index += 1;
		if(strstr(command_list[index].c_str(),"(")){
			command_list[index].erase(0,1);
			if(strstr(command_list[index].c_str(),"(")){
				//printf("The parentheses for a comparison was not in the front of the word.\n");
				output_test<<"The parentheses for a comparison was not in the front of the word."<<endl;
				return false;
			}
		} else{
			//printf("A parentheses was NOT included for a Selection\n");
			output_test<<"A parentheses was NOT included for a Selection"<<endl;
			return false;
		}
		if(contains_condition(command_list, index)){
			if(is_atomic(command_list, index)){
				return true;
			}
		}
	}
	return false;
}

bool is_identifier(string identifier){ //This asks if the statement is an identifier(basically if it can be a name)
	if(identifier.size()!=0){
		if(isalpha(identifier[0])){
			for(int i=0; i < identifier.size();i++){
				if (!isalnum(identifier[i])){
					if(identifier[i] != '_' && identifier[0] == '(' &&identifier[i] != ')' && identifier[i] != ','){ 
						//printf("%c is not a valid character.", identifier[i]);
						output_test<<"The character: "<<identifier[i]<<" in not a valid character"<<endl;
						return false;
					}
				}
			}
			return true;
		} else if(identifier[0] == '(' && (identifier.size() > 2)){
			if(isalpha(identifier[1])){
				for(int i=1; i < identifier.size();i++){
					if (!isalnum(identifier[i])){
						if(identifier[i] != '_' && identifier[0] == '(' &&identifier[i] != ')' && identifier[i] != ','){ 
							//printf("%c is not a valid character.", identifier[i]);
							output_test<<"The character: "<<identifier[i]<<" in not a valid character"<<endl;
							return false;
						}
					}
				}
				return true;
			}
		}
	}
	//printf("%s is not an identifier.", identifier.c_str());
	output_test<<"The word: "<<identifier.c_str()<<" is not a valid identifier."<<endl;
	return false;
}

bool is_atomic(vector<string> &command_list, int &index){ //This asks if the statement is an atomic expression
	if(is_identifier(command_list[index])){
		index + 1;
		return true;
	}
	if(strstr(command_list[index].c_str(),"(")){
		command_list[index].erase(0,1);
		if(strstr(command_list[index].c_str(),"(")){
			//printf("The parentheses for an Atomic Expression was not in the front of the expression.\n");
			output_test<<"The parentheses for an Atomic Expression was not in the front of the expression."<<endl;
			return false;
		}
	} else{
			//printf("A parentheses was NOT included for an Atomic Expression\n");
			output_test<<"A parentheses was NOT included for an Atomic Expression"<<endl;
			return false;
	}
	if(strstr(command_list[index].c_str(),")")){
		command_list[index].pop_back();
		if(!strstr(command_list[index].c_str(),")")){
			if(is_identifier(command_list[index])){
				return true;
			}
		}
		//printf("The parentheses for an Atomic Expression was not in the back of the expression.\n");
		output_test<<"The parentheses for an Atomic Expression was not in the back of the expression."<<endl;
		return false;
	}
	if(is_expr(command_list,index)){
		return true;
	}//printf("The argument provided for an Atomic Expression is unknown.\n");
	output_test<<"The argument provided for an Atomic Expression is unknown."<<endl;
	return false;
}

bool is_attribute_name_ForLoop(string identifier){ //This is used for Create
	if(identifier.size()!=0){
		if(isalpha(identifier[0])){
			for(int i=1; i+1 < identifier.size()-1;i++){
				if (!isalnum(identifier[i])){
					if(identifier[i] != '_'){
						printf("%s is not an identifier.", identifier.c_str());
						output_test<<"The word: "<<identifier.c_str()<<" is not an identifier"<<endl;
						return false;
					}
				}
			}
			if(strstr(identifier.c_str(),",")){
				identifier.pop_back();
				return true;
			} else{return false;}
		} else{output_test<<"first letter is not an alpha."<<endl;}
	} else{
		output_test<<"There was an empty Attribute List"<<endl;
		return false;
	}
	output_test<<"There was an unknown error in Attribute List."<<endl;
	return false;
}

bool contains_attribute_list(vector<string> &command_list, int &index){ //This asks if the pattern is right for attribute list
	if(index >= (command_list.size())){
		output_test<<"There was not enough arguments for an Attribute List."<<endl;
		return false;
	}
	if(strstr(command_list[index].c_str(),")")){
		return true;
	}
	if(strstr(command_list[index].c_str(),"(")){
		command_list[index].erase(0,1);
	} else{
		output_test<<"You need a \"(\" at the begining of an Attribute List."<<endl;
		return false;
	}

	for (int i = index; i < command_list.size();i++){
		index = i;
		if(!is_attribute_name_ForLoop(command_list[index])){
			if(strstr(command_list[i].c_str(),")")){
				command_list[i].pop_back();
					return true; 
			} else {
				output_test<<"There was not a comma in an Attribute List."<<endl;
				return false;
			}
		}
	}
	return false;
}

bool is_projection(vector<string> &command_list, int &index){ //This asks if the statement is a projection
	if(command_list[index] == "project"){
		index += 1;
		if(strstr(command_list[index].c_str(),"(")){
			command_list[index].erase(0,1);
			if(strstr(command_list[index].c_str(),"(")){
				output_test<<"The parentheses for a projection was not at the begining of the first argument."<<endl;
				return false;
			}
		}else {
			output_test<<"A parentheses is needed when calling an Attribute List for Projection."<<endl;
			return false;
		}
		if(contains_attribute_list(command_list, index)){
			if(is_atomic(command_list, index)){
				return true;
			} else{return false;}//Done to display correct Error Message
		}
	} output_test<<"An unknown error occured in Projection."<<endl;
	return false;
}

bool is_renaming(vector<string> &command_list, int &index){ //This asks if the statement is a rename
	if(command_list[index] == "rename"){
		index += 1;
		if(strstr(command_list[index].c_str(),"(")){
		} else{
			output_test<<"A parentheses is needed when calling an Attribute List for Renaming."<<endl;
			return false;
		}
		if(contains_attribute_list(command_list, index)){
			if(is_atomic(command_list, index)){
				return true;
			} else{return false;} //Done to display correct Error Message
		}
	}output_test<<"An unknown error occured in Renaming."<<endl;
	return false;
}

int is_udp(vector<string> &command_list, int &index){ //This asks if the statement is a union, difference, or product
	int return_val = 0;
	if(is_atomic(command_list,index)){
		index+=1;
		if(command_list[index].size() != 1){
			//printf("%s is too big to be a valid operation.", command_list[index].c_str());
			output_test<<"The phrase: "<<command_list[index].c_str()<<"is too big to be a vaild operation"<<endl;
			return false;
		}
		if(command_list[index] == "+"){
			return_val = 1; //union
		} else if(command_list[index]  == "-"){
			return_val = 2; //difference
		} else if(command_list[index]  == "*"){
			return_val = 3; //product
		} else{
			//printf("%s is not a valid operation.", command_list[index].c_str());
			output_test<<"The following: "<<command_list[index].c_str()<<" is not a vaild operation"<<endl;
			return 0;
		}
		index+=1;
		if(is_atomic(command_list,index)){
			return return_val;
		} else{return 0;}//Done to display correct Error Message
	}
	return 0;
}

bool is_expr(vector<string> &command_list, int &index){ //This asks if the statement is an expression
	if (command_list[index] == "select"){
		if(is_selection(command_list,index)){
			return true;
		}
	} else if (command_list[index] == "rename"){
		if(is_renaming(command_list,index)){
			return true;
		}
	} else if (command_list[index] == "project"){ 
		if(is_projection(command_list,index)){
			return true;
		}
	} else if (is_udp(command_list,index) == 1 || is_udp(command_list,index) == 2 || is_udp(command_list,index) == 3){
		return true;
	}
	return false;
}

bool is_query(vector<string> &command_list, int &index){ //This asks if the statement is a query
	if(command_list.size() > (index + 3)){
		for(int i=index; i< command_list.size();i++){
			if (is_identifier(command_list[index])){
				index+=1;
				if (command_list[index] == "<-"){
					index+=1; 
					if(!is_expr(command_list,index)){
						return false;
					} else{
						if (is_atomic(command_list,index)){
							return true;
						} else{
							return false;
						}
					}
				} else{return false;}
				i=index;
			} else{return false;}
		}
	} else{
		if(command_list.size() > 2){
			if (is_identifier(command_list[index])){
				index+=1;
				if (command_list[index] == "<-"){
					index+=1;
					if (is_identifier(command_list[index])){
						return true;
					}else{
						return false;
					}
				}
			}
		} else if(command_list[index] == "EXIT"){
			return true;
		}
		output_test<<"Not enough Arugements given for a query"<<endl;
		return false;
	} 
	return true;
}

bool is_type_wo(vector<string> &command_list, int &index){ //This asks if the statement is a type without commas
	if(command_list[index] != "INTEGER"){
		index += 1;
		if(command_list[index] != "VARCHAR"){
			index += 1;
			if(strstr(command_list[index].c_str(),")") && strstr(command_list[index].c_str(),"(")){
				command_list[index].pop_back();
				if (all_of(command_list[index].begin(), command_list[index].end(), ::isdigit)){
					index += 1;
					return true;
				}
			}
		}
	}else{
		index += 1;
		return true;
	}
	return false;
}

bool is_var(string var){ //This asks if the statement is a VARCHAR
	if(var.size()>8){
		if(var[0]=='V'){//The layout was made like this for debugging,
			if(var[1]=='A'){//but I liked how it looked, so I kept it.
				if(var[2]=='R'){
					if (var[3]=='C'){
						if(var[4]=='H'){
							if(var[5]=='A'){
								if(var[6]=='R'){
									if(var[7]=='('){
										for(int i=8; i<var.size()-2;i++){
											if(!isdigit(var[i])){
												return false;
											}
										}
										if(var[var.size()-1]==')'){
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}else{return false;}
	return false;
}

bool is_type(vector<string> &command_list, int &index){//This is to see if it is a type
	index -= 2;
	if(command_list[index] != "INTEGER"){
		index += 1;//IGNORE the Relation name
		command_list[index].pop_back();
		if(is_var(command_list[index])){
			index +=1;
			return true;
		}
	}else{
		index += 1;
		return true;
	}
	return false;
}

bool is_attribute_type_ForLoop(vector<string> command_list, int &index){//This is used to non-create commands
	for(int i=index; i < command_list.size(); i++){
		if(is_identifier(command_list[i])){
			i+=1;
			index=i;
			if(!is_type(command_list,i)){
				if (strstr(command_list[i].c_str(),")")){
					command_list[i].pop_back();
					if(is_type_wo(command_list,i)){
						return true;
					}
				} else{return false;}
				return false;
			}
		}else{return false;}
	}
	return false;
}

bool contains_attribute_type(vector<string> &command_list, int &index){ //This is used to see if the statement contains typed-attribute list
	int also =0; int no_loop=0;
	if(index >= (command_list.size() - 1)){
		output_test<<"There was not enough arguments for a typed Attribute List"<<endl;
		return false;
	}
	if(!strstr(command_list[index].c_str(),"(")){
		return false;
	}
	for (int i = index; i < command_list.size();i++){
		if(is_identifier(command_list[i])){
			if((command_list.size() - i)>1){
				if(!is_attribute_type_ForLoop(command_list,i)){
					if(strstr(command_list[i].c_str(),")")){
						no_loop=0;
						if(strstr(command_list[i].c_str(),",")){
							command_list[i].pop_back();
							also+=1; no_loop=1;
						}
						if(strstr(command_list[i].c_str(),"VARCHAR(")&& strstr(command_list[i].c_str(),"))")){
							command_list[i].pop_back();
							also+=2;
						}
						command_list[i].pop_back();
						if((!strstr(command_list[i].c_str(),")") && no_loop==0) || command_list[i] == "INTEGER"){
							index=i+also-1;
							return true; 
						} else if(no_loop==0){return false;}
						if(no_loop==0){
							output_test<<"There was no closing parentheses for an Attribute List."<<endl;
						}
					} else{return false;}
					if(no_loop==0){return false;}
				}
				
			}
		}
	}
	return false;
}

bool is_command(vector<string> command_list, int &index){//This is used to tell if the statement is a command
	if (command_list[index] == "OPEN"){
		if(is_identifier(command_list[index+=1])){
			return true;
		} else {
			//printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
			output_test<<"The following: "<<command_list[index=1].c_str()<<"is not a valid Relation Name"<<endl;
			return false;
		}
	} else if(command_list[index] == "CLOSE"){
		if(is_identifier(command_list[index+=1])){
			return true;
		} else {
			//printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
			output_test<<"The following: "<<command_list[index=1].c_str()<<"is not a valid Relation Name"<<endl;
			return false;
		}
	} else if(command_list[index] == "SAVE"){
		if(is_identifier(command_list[index+=1])){
			return true;
		} else {
			//printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
			output_test<<"The following: "<<command_list[index=1].c_str()<<"is not a valid Relation Name"<<endl;
			return false;
		}
	} else if(command_list[index] == "EXIT"){
		return true;
	} else if(command_list[index] == "SHOW"){
		if(is_atomic(command_list,index+=1)){
			return true;
		} else {return false;}
	} else if (command_list[index] == "CREATE"){
		if(command_list.size() >= (index)){
			if(command_list[index+=1] == "TABLE"){
				if(is_identifier(command_list[index+=1])){
					if(strstr(command_list[index+=1].c_str(),"(")){
							if(contains_attribute_type(command_list, index)){
								if(command_list[index] == "PRIMARY"){
									if(command_list[index+=1] == "KEY"){
										if(contains_attribute_list(command_list, index+=1)){return true;}
									}
								}
							}
					} else{output_test<<"Must have a begining parentheses before Typed Attribute-list."<<endl;}
				}
				return false;
			} else{
				output_test<<"TABLE must be included after \"Create\"."<<endl;
				return false;
			}
		} else{
			output_test<<"There were not enough arguments for create"<<endl;
			return false;
		}
	} else if(command_list[index] == "UPDATE"){
		if(command_list.size() > (index +6)){
			if(is_identifier(command_list[index+=1])){
				if(command_list[index+=1] != "SET"){
					return false;
				}
				if (!is_identifier(command_list[index+=1])){
					return false;
				}
				if (command_list[index+=1] != "="){
					return false;
				}
				if(!strstr(command_list[index+=1].c_str(),",")){
					return false;
				}
				for(int i = index+3; i < command_list.size()+3;i++){
					if(command_list[i] != "SET" || !is_identifier(command_list[i+1]) || command_list[i+2] != "=" ){
						if(strstr(command_list[i+3].c_str(),",") && command_list[i+4] == "WHERE"){
							return false;
						}
						if(!strstr(command_list[i+3].c_str(),",") && command_list[i+4] != "WHERE"){
							return false;
						}
					}
					i+=2;
					index=i;
				}
				if(command_list[index+=1] == "WHERE"){
					if(contains_condition(command_list, index+=1)){
						return true;
					}
				}
			}
		}
		return false;
	} else if(command_list[index] == "INSERT"){
		if(command_list.size() > (index +5)){
			if(command_list[index+1] == "INTO" && is_identifier(command_list[index+2]) && command_list[index+3] == "VALUES" && command_list[index+4] == "FROM"){
				if(command_list[index+5] == "RELATION"){
					if(is_expr(command_list, index+=6)){
						return true;
					} else {return false;}
				} else if(strstr(command_list[index+5].c_str(),"(") && strstr(command_list[index+5].c_str(),",")){
					for (int i=index+5; i < command_list.size();i++){
						if(!strstr(command_list[i].c_str(),",")){
							if(strstr(command_list[i].c_str(),")")){
								index = i;
								return true;
							} else {return false;}
						}
					}	
				} else if(strstr(command_list[index+5].c_str(),"(") && strstr(command_list[index+5].c_str(),")")){
					return true;
				} else {return false;}
			}
		}
		return false;
	} else if(command_list[index] == "DELETE"){
		if(command_list.size() > (index +2)){
			if(command_list[index+1] == "FROM" && is_identifier(command_list[index+2]) && command_list[index+2] == "WHERE"){
				if (contains_condition(command_list, index+=2)){
					return true;
				}
			}
		}
		return false;
	}
}

bool equal_parentheses(vector<string> command_list){//This eliminates some statements immiedately
	int number_of_beg_parenthesis=0;
	int number_of_end_parenthesis=0;
	if(command_list.size()>0){
		for(int i=0; i < command_list.size();i++){
			if(strstr(command_list[i].c_str(),"(")){
				number_of_beg_parenthesis += count(command_list[i].begin(), command_list[i].end(), '(');
			}
			if(strstr(command_list[i].c_str(),")")){
				number_of_end_parenthesis += count(command_list[i].begin(), command_list[i].end(), ')');
			}
		}
	} else{number_of_end_parenthesis=1;}//Return False (Preventing a SegFault)
	return (number_of_beg_parenthesis == number_of_end_parenthesis);
}

bool main_loop(vector<string> &command_list, int &line_number, Database &d){
	if(command_list.size()>0){
		command_list[command_list.size()-1].erase(std::remove(command_list[command_list.size()-1].begin(), command_list[command_list.size()-1].end(), ';'), command_list[command_list.size()-1].end());
		if(equal_parentheses(command_list)){
			int num=0; int num2=0;
			if(is_command(command_list, num2)){
				if(command_list[0]=="EXIT"){exit(0);}//Saves time
				//Action(d, command_list);
				output_test << "line " << to_string(line_number) <<"was successful!"<<endl;
				return true;
			}else if(is_query(command_list, num)){
				//Action(d, command_list);
				output_test << "line " << to_string(line_number) <<"was successful!"<<endl;
				return true;
			}else {
				//cout<<"\nThis is NOT a valid statement. This was given on index: " << num << endl;
				output_test << "line " << to_string(line_number) <<" failed: NOT VALID! INDEX: "<< num <<endl;
				return false;
			}
		} else{
		//cout << "There are not an equal number of begining and ending parentheses.\n";
		output_test << "line " << to_string(line_number) <<" failed: unequal # of parentheses."<<endl;
		return false;
		}
	} else{
		output_test << "line " << line_number <<" failed: There is not enough arguments"<<endl;
		return false;
	}
	line_number++;
}

bool valid(string command, string filename, int line_number){
	string out_name = "Parser/out/Output_"+filename+"_"+std::to_string(line_number)+".txt";
	output_test.open (out_name);
	Database temp("temp");
	stringstream ss(command);
	cout<<command<<'\n';
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> command_list(begin, end);
	return main_loop(command_list, line_number,temp);
}