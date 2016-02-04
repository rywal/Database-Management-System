#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

void EXIT();

using namespace std;

template<class V>
void vector_out(const vector<V>& vector){
	cout << "Data: ";
	copy(vector.begin(), vector.end(), 
		ostream_iterator<V>(cout, " "));
	cout << '\n';
};

int main(){
	
	ofstream outfile;
	outfile.open("records.txt");
	
	
	string data;
	char character;
	vector<char> characters;
	
	cout << "Enter characters: ";
	getline(cin, data);
	istringstream stream(data);
	while (stream >> character)
		characters.push_back(character);
	
	vector_out(characters);
	
	
	outfile << data;
	outfile.close();

};

void EXIT(){
	exit(0);
}
