#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>


using namespace std;

int main(){


cout << "Hello \n";
	
ofstream outfile;
outfile.open ("notes.txt");
outfile << "Hello" << endl;
outfile.close();

	return 0;
}



// Relational and comparison operators ==,!=,<,>,<=,>=

/*
class comparison{
private:
	string f;
	string g;
public:
	bool comp (string f, string g);
	
};

bool comp (string f, string g){
	return ( f || g);
	
};	



//---------------------------------------------------

class conjuction{
private:
	string d;
	string e;
public:
	bool s (string d, string e);
	
};

bool s (string d, string e){
	return ( string d && string e);
};

*/

//---------------------------------------------------
class comparison {
private:
	string a;
	string b;
	string c;

public:
	bool eqeq (string a, string b);
	bool noteq (string a, string b);
	bool great (string a, string b);
	bool greateq (string a, string b);
	bool less (string a, string b);
	bool lesseq (string a, string b);
};

bool eqeq (string a, string b){
	return (a == b);
};

bool noteq (string a, string b){
	return !(a ==b);
};

bool great (string a, string b){
	return (a > b);
};

bool greateq (string a, string b){
	return (a >= b);
};

bool less (string a, string b){
	return (a < b);
};

bool lesseq (string a, string b){
	return (a <= b);
};


// close-cmd | save-cmd | exit-cmd

/*
close-cmd ::== CLOSE relation-name 
save-cmd ::== SAVE relation-name 
exit-cmd ::== EXIT 
*/
class close{
	
	
};

//-----------------------------------------
class save{
	
	
};


class exit{
	
	
};





