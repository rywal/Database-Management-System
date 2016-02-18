#include "../DBCore/Database.h"
#include "string.h"
#include <boost/algorithm/string.hpp>
#include "test_parser.h"//

bool is_command(string command){
        //uses ascii to check if the first letter is uppercase
        return (command[0]>65 && command[0]<90);
}

bool is_query(string command){
        //uses ascii to check if the first letter is lowercase
        return ((command[0]>96 && command[0]<123)||command[0]==95);
}
//declare functions for recursive use
Relation make_query(Database &d, vector<string> query);
string which_op(string a);
void make_command(Database &d, vector<string> query);
//
void make_update(){}

vector<string> make_insert(vector<string> command){
		vector<string> values; 
		for (int i=5; i < command.size(); i++){
			if (command[i].front()=='"'){
				command[i].erase(std::remove(command[i].begin(), command[i].end(), '"'), command[i].end());
            } //printf("%s function, line: %d\n\n", __func__, __LINE__);
			//gets rid of ) and ,
            command[i].erase(std::remove(command[i].begin(), command[i].end(), ','), command[i].end());
			command[i].erase(std::remove(command[i].begin(), command[i].end(), ')'), command[i].end());
            std::cout << "Inserting value: " << command[i] << "\n";
			//makes a string of data values for insert
			values.push_back(command[i]);
		} 
	return values;
}


Relation make_product(Database &d, vector<string> query, int &loop){ 
	if(query[2].front()=='('){
		cout<<"CP first route\n";
		query[query.size()-1].erase(query[query.size()-1].size()-1, 1);
		query[2].erase(0,1);
		vector<string> _query(query.begin() + 2, query.end());
		return d.cross_product(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else{
		cout<<"CP second route\n";
		vector<string> _query(query.begin() + 2, query.end());
		string expr=query[2];
		string expr1=expr.substr(0,expr.size()-1);
		cout<<query[0]<<" : "<<expr1<<endl;
		cout<<"loop: "<<loop<<endl; 
		if (loop = 1){
			loop = 0;
			return d.cross_product(" ", d.get_relation(query[0]), d.get_relation(expr1));
		} else{
			return d.cross_product(" ", d.get_relation(query[0]), d.get_relation(query[0]));
		}

	}
}

Relation make_difference(Database &d, vector<string> query){
	if(query[2].front()=='('){
		query[query.size()-1].erase(query[query.size()-1].size()-1, 1);
		query[2].erase(0,1);
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_difference(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else{
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_difference(" ", d.get_relation(query[0]), make_query(d, _query));
	}
}

Relation make_union(Database &d, vector<string> query){
	if(query[2].front()=='('){
		query[query.size()-1].erase(query[query.size()-1].size()-1, 1);
		query[2].erase(0,1);
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_union(" ", d.get_relation(query[0]), make_query(d, _query));	
	}
	else{
		vector<string> _query(query.begin() + 2, query.end());
		return d.set_union(" ", d.get_relation(query[0]), make_query(d, _query));
	}
}
 
//creates a selection
Relation make_select(Database &d, vector<string> query){
	//get rid of (
	if(query[0].front()=='(')
		query[0].erase(0,1);
	//declareand initialize the arguments for the select function
	string att_name=query[0];
	string compare=query[1];
	string value=query[2];
	//get rid of )
	value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
	int i;
//three cases:
	//1) the selection is at the end of it's conditions
	if(query[2].back()==')'){
		value.pop_back();
		if(query[3].front()=='('){query[3].erase(0,1);}
		vector<string> _query(query.begin() + 3, query.end());
        std::cout << "Selecting " << att_name << " with value " << value << " with operation " << which_op(compare) << endl;
		return d.select(att_name, value, which_op(compare), make_query(d, _query));
	} 
	//2) the selection is goin to set_difference two conditions
	else if( query[3]=="&&"){
		for(i=4; query[i].back()!=')'; i++){}
		vector<string> _query(query.begin() + i + 1, query.end());
		vector<string> _query2(query.begin() + 4, query.end());
		return d.set_difference(" ", d.select(att_name, value, which_op(compare), make_query(d, _query) ), make_select(d, _query2));
		
	}
	//3) the selection is going to set_union two conditions
	else if( query[3] =="||"){
		for(i=4; query[i].back()!=')'; i++){}
		vector<string> _query(query.begin() + i + 1, query.end());
		vector<string> _query2(query.begin() + 4, query.end());
		return d.set_union( " ", d.select(att_name, value, which_op(compare), make_query(d, _query) ), make_select(d, _query2));	
	}
}

Relation make_project(Database &d, vector<string> query){
	int i;
	vector<string> names;
	query[1].erase(0,1);
	for(i=1; query[i].back()!=')'; i++){
		//get rid of comma
		query[i].erase(query[i].size()-1, 1);
 		names.push_back( query[i]);
	}
	query[i].erase(query[i].size()-1, 1);
	names.push_back(query[i]);
	if (query[i+=1].front()=='('){
		cout<<"first route\n";
		query[i].erase(0,1);
		vector<string> _query(query.begin() + i, query.end());
		return d.project(names, make_query(d, _query));
	}
	else{
		cout<<"second route\n";
		vector<string> _query(query.begin() + i, query.end());
		return d.project(names, make_query(d,_query));	
	}
}

Relation make_rename(Database &d, vector<string> query){
	int i;
	vector<string> names;
	if(query[1].front()=='('){
		query[1].erase(0,1);
	}
	for(i=1; query[i].front()!='('; i++){
		//get rid of comma
		if(query[i].back()==',' || query[i].back()==')')
		query[i].erase(query[i].size()-1, 1);
 		names.push_back( query[i]);
	}
//two cases
	//1) the atomic-expr is an expr
	if (query[i].front()=='('){
		query[i].erase(0,1);
		vector<string> _query(query.begin() + i, query.end());
		//recursively call for another query 
		return d.renaming(" ", names, make_query(d, _query));
	}
	//2) the atomic-expr is a relation name
	else{
		vector<string> _query(query.begin() + i, query.end());
		return d.renaming(" ", names, make_query(d, _query));		
	}
}
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

void make_command(Database &d, vector<string> command){ 
	string Com = command[0];
	//this is to take care of a glitch in the program. An extra character was being added so we deleted it
	string temp=command[1].substr(0,command[1].size()-1);
	printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
//    string temp = command[1];
//Exit printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
		if(Com=="EXIT"){printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
			exit(0);printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
		}
//Show
		else if(Com=="SHOW"){
			if(temp.front()=='('){	//erase the (
				temp.erase(0,1);
				//create new vector for new query
				vector<string> _query(command.begin() + 1, command.end());
				d.show(make_query(d, _query));	
			}
            std::cout << "name of relation is " << temp << " with length: " << temp.length() << "\n";printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
			d.print_relation(d.get_relation(temp));
		}
//Save
		else if(Com=="SAVE"){
            string expr1=command[1].substr(0,command[1].size()-1);
            cout << "Saving " << expr1 << "with length" << expr1.length() << endl;
			d.save(expr1);
		}

			
//Open
		else if(Com=="OPEN"){printf("%s file, %s function, line: %d\n\n", __FILE__, __func__, __LINE__);
		//	d.open(d.get_relation(command[1]));
		}
//Close
		else if(Com=="CLOSE"){
            string expr1=command[1].substr(0,command[1].size()-1);
            cout << "Closing " << expr1 << "with length" << expr1.length() << endl;
            d.close(expr1);
		}
//Delete
		else if(Com=="DELETE"){
			vector<string> _query(command.begin() + 3, command.end());
			_query.push_back(command[2]);
		//	d.delete(d.get_relation(command[2]),make_select(d, _query));
		}

//Update
		else if(Com=="UPDATE"){
			vector<string> _query(command.begin() + 3, command.end());
			
			vector<string> names;
			vector<string> compare_values;
			vector<string> lit;
			vector<string> op_v;

			string relation_n = command[1];
			int loop = 1; int temp_ind=0;
			for(int i=0; i<_query.size(); i++){
				//get rid of comma
				names.push_back(_query[i]);
				i+2;
				if(!strstr(_query[i].c_str(),",")){loop=0;}
				_query[i].erase(std::remove(_query[i].begin(), _query[i].end(), ','), _query[i].end());
				lit.push_back(_query[i]);
				if(loop==0){loop==1;temp_ind=i;break;}
			}
			
			for(int i=temp_ind+1; i+2<_query.size(); i++){
				//get rid of comma
				op_v.push_back(_query[i]);
				i+1;
				compare_values.push_back(_query[i]);
			}
			

			for(int i=0; i<compare_values.size(); i++){
				d.update(d.get_relation(relation_n),names[i],op_v[i],compare_values[i],lit[i]);
			}
			
			
		//	d.update();
        }
    
//Insert
		else if (Com == "INSERT") { 
			if (command[5].front() == '(') { 
				command[5].erase(0,1);
				vector<string> _command(command.begin() + 5, command.end());
                Relation &r = d.get_relation(command[2]);
                std::cout << "inserting tuple\n";
				r.insert_tuple(make_insert(command));
			} 
			else { 
				vector<string> _query(command.begin() + 6, command.end());
                Relation &r = d.get_relation(command[2]);
				r.insert_relation(make_query(d, _query));
			}
		}
//Create
		else if(Com=="CREATE"){ 
			int i, length;
			string check;
			vector<string> att_names;
			vector<int> att_lengths;
			vector<string> primary; 
			command[3].erase(0,1); 
			//create the attribute_list
			for(i=4; command[i].back()!=')'; i+=2){ 
				//command[i].erase(std::remove(command[i].begin(), command[i].end(), ','), command[i].end()); 
				
				command[i].erase(command[i].size()-1, 1);
				
				
				att_names.push_back(command[i-1]); 
				check=command[i].substr(0,7); 
				if(check=="VARCHAR"){ 
					length=stoi(command[i].substr(8, command[i].size()-9)); 
					att_lengths.push_back(length); 
				}	
				else if(check=="INTEGER"){
					length=0; 
					att_lengths.push_back(length); 
				} 
			} 
			command[i].erase(std::remove(command[i].begin(), command[i].end(), ','), command[i].end()); 
			att_names.push_back(command[i-1]); 
			check=command[i].substr(0,7); 
			if(check=="VARCHAR"){ 
				length=stoi(command[i].substr(8, command[i].size()-9));	 				
				att_lengths.push_back(length); 
			}
			else if(check=="INTEGER"){ 
				length=0; 
				att_lengths.push_back(length); 
			}
//set the primary keys			 
			i+=3; 							//skip PRIMARY KEY
			command[i].erase(0,1);					//erase '(' 
			for(; command[i].back()!=')'; i++){	 
                command[i].erase(std::remove(command[i].begin(), command[i].end(), ','), command[i].end());
                cout << "Pushing back value to primary keys: " << command[i] << endl;
			
				if(strstr(command[i].c_str(),")")){
					command[i].erase(std::remove(command[i].begin(), command[i].end(), ')'), command[i].end());
					primary.push_back(command[i]);
					command[i]+=")";
				} else {primary.push_back(command[i]);}
				
				
				if(strstr(command[i].c_str(),")")){break;}
			}
//			primary.push_back(command[i]);
			d.create_relation(command[2], att_names, att_lengths, primary);
		
		}

}

Relation make_query(Database &d, vector<string> query){
	string expr=query[0];
	if(1==query.size()){
		string expr1=expr.substr(0,expr.size()-1);
		return d.get_relation(expr1);
	}
    expr = query[0];
	//Renaming
	if (expr == "rename")
		return make_rename(d, query);
    //Projection
    else if (expr == "project")
		return make_project(d, query);
	//Selection
	else if (expr == "select"){
		vector<string> _query(query.begin() + 1, query.end());	
		return make_select(d, _query);
	}
		//relation cases n
		//just a relation name
	else if(loop==1){
		string expr2=query[1];
		//Product
		int loop = 1;
		if (expr2 == "*")
				return make_product( d, query, loop);
		//Difference
		else if (expr2	== "-")
				return make_difference( d, query);
		//Union
		else if (expr2 == "+")
				return make_union( d, query);
		
	}
}


void Action(Database &d, vector<string> command){
   // command[command.size()-1].pop_back();
	
	if(is_command(command[0])){ 
                make_command(d, command); 
	}else if(is_query(command[0])){
		vector<string> query(command.begin() + 2, command.end());
               d.create_relation(command[0], make_query(d, query));
	}else {}//error
}

void main_loop(vector<string> &command_list, string &command, int &line_number, Database &d){
	if(command_list.size()>0){
		command_list[command_list.size()-1].erase(std::remove(command_list[command_list.size()-1].begin(), command_list[command_list.size()-1].end(), ';'), command_list[command_list.size()-1].end());
		if(equal_parentheses(command_list)){
			int num=0; int num2=0;
			if(is_command(command_list, num2)){
				Action(d, command_list);
				output << "line " << to_string(line_number) <<"was successful!"<<endl;
			}else if(is_query(command_list, num)){
				Action(d, command_list);
				output << "line " << to_string(line_number) <<"was successful!"<<endl;
			}else {
				cout<<"\nThis is NOT a valid statement. This was given on index: " << num << endl;
				output << "line " << to_string(line_number) <<" failed"<<endl;
			}
		} else{
		cout << "There are not an equal number of begining and ending parentheses.\n";
		output << "line " << to_string(line_number) <<" failed"<<endl;
		}
	} else{
		cout << "There is not enough arguments" << endl;
		output << "line " << to_string(line_number) <<" failed"<<endl;
	}
	line_number++;
}

int main(){
	output.open ("Output.txt");
	Database d("d");
	if(!output){ //This should never happen
		printf("\nThe Output file is not found!");
		exit(EXIT_FAILURE);//Showing error status code
	}
	printf("This is the Beginning of %s, in the %s function, which is on line: %d\n\n", __FILE__, __func__, __LINE__);//This is for error management
	string f_or_h;
	printf("For this run, would you like to take input from an \"Input.txt\" file [f], or type commands in by hand[h]? [f\\h]\n>");//Giving better testing handles
	cin >>  f_or_h;
	int loop=1;
	while (loop==1){
		if(f_or_h != "h" && f_or_h != "H" && f_or_h != "hand" && f_or_h != "f" && f_or_h != "F" && f_or_h != "file"){
			std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
			f_or_h = "";
			printf("Please re-enter your prefered input method [f\\h]\n>");
			cin >>  f_or_h;
		} else{loop=0;}
	}
	if(f_or_h == "f" || f_or_h == "F" || f_or_h == "file"){
		string command;
		string input_file = "";
			printf("Please input the file you would like to use. \n(Please note, this is automated, no other input will be read)\n>");
			cin >> input_file;
			std::ifstream input(input_file);
			if(!input){
				printf("\nThe input file not found!");
				printf("\nPlease place a file named \"Input.txt\" in the same folder as %s.\n\n", __FILE__);
				exit(EXIT_FAILURE);//Showing error status code
			}
		int line_number=1;
		while(std::getline(input, command)){ 
			cout << "\nThe command given is: " << command.c_str() << endl;
			vector<string> command_list;
			boost::split(command_list, command, boost::is_any_of(" "));
			main_loop(command_list, command, line_number,d);
		}
		input.close();
	} else if (f_or_h == "h" || f_or_h == "H" || f_or_h == "hand"){
		int line_number=1;
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
		}
	}
	output.close();
	return 0;
}

	
