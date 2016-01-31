#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>


using namespace std;

int main(){

	cout << "Hello \n";

	return 0;}



// Relational and comparison operators ==,!=,<,>,<=,>=

class conjuction{




};

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


