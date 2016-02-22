#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../DBCore/Database.h"

using namespace std;

Database rdbms("db");

void create_exhibits_table() {
    string name = "exhibits";
    vector<string> attribute_names {"company", "address", "contact", "email", "phone", "fax", "category", "booth_personnel", "description", "website"};
    vector<int> attribute_types {20, 100, 20, 20, 15, 15, 0, 400, 500, 100};
    vector<string> primary_keys {"company"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_booths_table() {
    string name = "booths";
    vector<string> attribute_names {"starting_row", "ending_row", "column", "type"};
    vector<int> attribute_types {0, 0, 0, 0};
    vector<string> primary_keys {"starting_row", "ending_row", "column"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_services_table() {
    string name = "";
    vector<string> attribute_names {""};
    vector<int> attribute_types {};
    vector<string> primary_keys {""};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_attendees_table() {
    string name = "";
    vector<string> attribute_names {""};
    vector<int> attribute_types {};
    vector<string> primary_keys {""};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_inventory_table() {
    string name = "";
    vector<string> attribute_names {""};
    vector<int> attribute_types {};
    vector<string> primary_keys {""};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

int main(){
    create_exhibits_table();
    create_booths_table();
    
	int select;
	
	cout << "\n Welcome to The Convention Exhibit Management System \n";
	cout << " ----------------------------------------------- \n \n ";
	cout << "1. Exhibit Manager \n 2. Exhibitor \n 3. Attendee \n 4. Exit \n \n";
	cout << "Please select which data records you would like to access: ";
	cin >> select;
	
	return 0;
}