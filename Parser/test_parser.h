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
ofstream output;
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
		printf("%s is not a valid operator", op.c_str());
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
			printf("The amount of parentheses given for an operator combo is incorrect.\n");
			return false;
		}
	}else{return false;}
	printf("There was an unknown error in operator combo.\nPlease re-compile this and re-run command.\n\n");
	return false;
}


bool contains_comparison(vector<string> &command_list, int &index){ //This asks if the pattern is correct for a comparision
	for (int i = index; i < command_list.size();i++){
		if (!contains_operand_combo(command_list, i)){
			if(strstr(command_list[i].c_str(),"(")){
				command_list[i].erase(0,1);
				if(strstr(command_list[i].c_str(),"(")){
					printf("The parentheses for a comparison was not in the front of the word.\n");
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
					printf("The || operator is needed inbetween conjunctions.\n");
					return false;
				}
			}
			i+=1;
			if(!contains_conjunction(command_list, i)){
				printf("The argument provided for a condition is unknown.\n");
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
				printf("The parentheses for a comparison was not in the front of the word.\n");
				return false;
			}
		} else{
			printf("A parentheses was NOT included for a Selection\n");
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
						printf("%c is not a valid character.", identifier[i]); 
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
							printf("%c is not a valid character.", identifier[i]);
							return false;
						}
					}
				}
				return true;
			}
		}
	}
	printf("%s is not an identifier.", identifier.c_str());
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
			printf("The parentheses for an Atomic Expression was not in the front of the expression.\n");
			return false;
		}
	} else{
			printf("A parentheses was NOT included for an Atomic Expression\n");
			return false;
	}
	if(strstr(command_list[index].c_str(),")")){
		command_list[index].pop_back();
		if(!strstr(command_list[index].c_str(),")")){
			if(is_identifier(command_list[index])){
				return true;
			}
		}
		printf("The parentheses for an Atomic Expression was not in the back of the expression.\n");
		return false;
	}
	if(is_expr(command_list,index)){
		return true;
	}printf("The argument provided for an Atomic Expression is unknown.\n");
	return false;
}

bool is_attribute_name_ForLoop(string identifier){ //This is used for Create
	if(identifier.size()!=0){
		if(isalpha(identifier[0])){
			for(int i=1; i+1 < identifier.size()-1;i++){
				if (!isalnum(identifier[i])){
					if(identifier[i] != '_'){
						printf("%s is not an identifier.", identifier.c_str());
						return false;
					}
				}
			}
			if(strstr(identifier.c_str(),",")){
				identifier.pop_back();
				/*if(strstr(identifier.c_str(),",")){
					printf("There was not a comma inbetween a List.\n");
					return false;
				}*/
				return true;
			} else{return false;}
		} else{printf("first letter is not an alpha.\n");}
	} else{
		printf("There was an empty Attribute List\n");
		return false;
	}
	printf("There was an unknown error in Attribute List.\n");
	return false;
}

bool contains_attribute_list(vector<string> &command_list, int &index){ //This asks if the pattern is right for attribute list
	if(index >= (command_list.size())){
		printf("There was not enough arguments for an Attribute List\n");
		return false;
	}
	if(strstr(command_list[index].c_str(),")")){
		return true;
	}
	if(strstr(command_list[index].c_str(),"(")){
		command_list[index].erase(0,1);
	} else{
		printf("You need a \"(\" at the begining of an Attribute List\n");
		return false;
	}

	for (int i = index; i < command_list.size();i++){
		index = i;
		if(!is_attribute_name_ForLoop(command_list[index])){
			if(strstr(command_list[i].c_str(),")")){
				command_list[i].pop_back();
					return true; 
			} else {
				printf("There was not a comma in an Attribute List236.\n");
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
				printf("The parentheses for a projection was not at the begining of the first argument.\n");
				return false;
			}
		}else {
			printf("A parentheses is needed when calling an Attribute List for Projection.\n");
			return false;
		}
		if(contains_attribute_list(command_list, index)){
			if(is_atomic(command_list, index)){
				return true;
			} else{return false;}//Done to display correct Error Message
		}
	} printf("An unknown error occured in Projection.\n");
	return false;
}

bool is_renaming(vector<string> &command_list, int &index){ //This asks if the statement is a rename
	if(command_list[index] == "rename"){
		index += 1;
		if(strstr(command_list[index].c_str(),"(")){
		} else{
			printf("A parentheses is needed when calling an Attribute List for Renaming.\n");
			return false;
		}
		if(contains_attribute_list(command_list, index)){
			if(is_atomic(command_list, index)){
				return true;
			} else{return false;} //Done to display correct Error Message
		}
	}printf("An unknown error occured in Renaming.\n");
	return false;
}

int is_udp(vector<string> &command_list, int &index){ //This asks if the statement is a union, difference, or product
	int return_val = 0;
	if(is_atomic(command_list,index)){
		index+=1;
		if(command_list[index].size() != 1){
			printf("%s is too big to be a valid operation.", command_list[index].c_str());
			return false;
		}
		if(command_list[index] == "+"){
			return_val = 1; //union
		} else if(command_list[index]  == "-"){
			return_val = 2; //difference
		} else if(command_list[index]  == "*"){
			return_val = 3; //product
		} else{
			printf("%s is not a valid operation.", command_list[index].c_str());
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
	} /*else if (is_atomic(command_list,index)){
		return true;
	}*/
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
		printf("Not enough Arugements given");
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
		printf("There was not enough arguments for a typed Attribute List\n");
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
						if(no_loop==0){printf("There was no closing parentheses for an Attribute List.\n");}
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
			printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
			return false;
		}
	} else if(command_list[index] == "CLOSE"){
		if(is_identifier(command_list[index+=1])){
			return true;
		} else {
			printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
			return false;
		}
	} else if(command_list[index] == "SAVE"){
		if(is_identifier(command_list[index+=1])){
			return true;
		} else {
			printf("%s is not a valid Relation Name\n", command_list[index=1].c_str());
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
					} else{printf("Must have a begining parentheses before Typed Attribute-list\n");}
				}
				return false;
			} else{
				printf("TABLE must be included after \"Create\"\n");
				return false;
			}
		} else{
			printf("There were not enough arguments for create\n");
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
				if(!strstr(command_list[index+=1].c_str(),",")){ cout<<"562"<<endl;
					return false;
				}
				for(int i = index+3; i < command_list.size()+3;i++){ cout<<"565"<<endl;
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
					if(contains_condition(command_list, index+=1)){cout<<"This is true"<<endl;
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
