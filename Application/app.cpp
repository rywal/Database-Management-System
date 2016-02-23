#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../DBCore/Database.h"

#define EXHIBIT_MANAGER 1
#define EXHIBITOR 2
#define ATTENDEE 3

using namespace std;

Database rdbms("db");

// Create needed tables
void create_exhibits_table() {
    string name = "exhibits";
    vector<string> attribute_names {"company", "address", "contact", "email", "phone", "fax", "category", "booth_personnel", "description", "website"};
    vector<int> attribute_types {20, 100, 20, 20, 15, 15, 0, 100, 100, 50};
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

// Exhibitors
void list_exhibitors(bool with_criteria) {
    // If criteria is needed, get it
    if (with_criteria) {
        string criteria;
        cout << "Input your criteria in the grammar of the DML: ";
        cin >> criteria;

        if (criteria.length() <= 0) {
            cout << "Warning: Criteria was not given. Proceeding as if it was not required";
            with_criteria = false;
        } else {
        	string query = "SELECT FROM exhibits WHERE " + criteria + ";";
            // TODO: Need to check this input for validity and then plug it into a select query
        }
    }
    
    // Fetch proper list of exhibitors and print
    if (with_criteria) {
        Relation &list_relation = rdbms.get_relation("exhibits");
        rdbms.app_print_relation( list_relation );
    } else {
        Relation list_relation = rdbms.get_relation("exhibits");
        rdbms.app_print_relation( list_relation );
    }
}

void register_exhibitor() {
    vector<string> fields {"company", "address", "contact", "email", "phone", "fax", "category", "booth_personnel", "description", "website"};
    vector<string> values;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    for (string f : fields) {
        cout << "Please input value for " << f << ": ";
        string input;
        getline( cin, input );
        values.push_back( input );
    }
    
    rdbms.get_relation("exhibits").insert_tuple( values );
}


// Display menus
void display_welcome_message(){
    cout << "\nWelcome to The Convention Exhibit Management System\n";
    cout << "----------------------------------------------- \n \n";
    cout << "1. Exhibit Manager \n2. Exhibitor \n3. Attendee \n4. Exit\n\n";
    cout << "Please select which data records you would like to access: ";
}

void display_exhibits_menu() {
    cout << "\nExhibits\n";
    cout << "----------\n";
    cout << "E1. List Exhibitors\n";
    cout << "E2. List Exhibitors(based on criteria)\n";
    cout << "E3. Register new Exhibitor\n";
    cout << "E4. Remove Exhibitor(s)\n\n";
}

// TODO: Implement this along with the rest of the menus
void display_booths_menu() {
    cout << "\nBooths\n";
    cout << "----------\n";
    cout << "B1. \n";
    cout << "B2. \n";
    cout << "B3. \n";
}

void display_services_menu() {}
void display_finance_menu() {}
void display_attendees_menu() {}
void display_inventory_menu() {}

// Intepret the given command
bool interpret_command(string command){
    if (command.at(0) == 'Q' || command.length() < 2) {
        // Quit command given
        return true;
    }
    
    // Get the second character in the given command
    int sub_command = command.at(1) - '0';
    cout << "Command given: " << command << " breaks down to have a sub_command of: " << sub_command << "\n";
    
    // Quit command not given, continue parsing
    if (command.at(0) == 'E') {
        // Exhibits menu
        switch (sub_command) {
            case 1:
                list_exhibitors(false);
                break;
                
            case 2:
                list_exhibitors(true);
                break;
                
            case 3:
                register_exhibitor();
                break;
                
            case 4:
//                remove_exhibitor();
                break;
        }
    } else if (command.at(0) == 'B'){
        // Booths menu
        
    } else if (command.at(0) == 'S'){
        // Services menu
        
    } else if (command.at(0) == 'F'){
        // Finance menu
        
    } else if (command.at(0) == 'A'){
        // Attendees menu
        
    } else if (command.at(0) == 'I'){
        // Inventory menu
        
    } else {
        // Command not found
        cout << "Command '" << command << "' not found.\n";
        return true;
    }
    
    return false;
}

int main(){
    create_exhibits_table();
    create_booths_table();
    // TODO: Add in the rest of the create functions
    // create_NAME_table();
    
    // Find user's role
	int role = -1;
    while (role < 0) {
        display_welcome_message();
        cin >> role;
        
        switch (role) {
            case EXHIBIT_MANAGER: // Exhibit Manager
                break;
            case EXHIBITOR: // Exhibitor
                break;
            case ATTENDEE: // Attendee
                break;
            case 4:
                return 0;
                break;
            default:
                role = -1;
                cout << "ERROR: Please enter input based on the instructions\n";
                break;
        }
    }
    
    // Display menus based on user's role
    string next_command = "";
    bool stop = false;
    while (!stop) {
        if (role == EXHIBIT_MANAGER){
            display_exhibits_menu();
            // TODO: Fill in rest of applicable menus here
            cout << "Input your command: ";
            
            cin >> next_command;
            stop = interpret_command(next_command);
        } else if (role == EXHIBITOR) {
            
        } else if (role == ATTENDEE) {
            
        }
    }
	
	return 0;
}