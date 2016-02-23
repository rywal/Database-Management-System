#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../Parser/ryanparser.h"

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
    vector<string> attribute_names {"company", "starting_row", "ending_row", "column", "type"};
    vector<int> attribute_types {20, 0, 0, 0, 0};
    vector<string> primary_keys {"company", "starting_row", "ending_row", "column"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_services_table() {
    string name = "services";
    vector<string> attribute_names {"electricity", "furniture", "electronics", "barcode_scanner", "advertisement", "insurance"};
    vector<int> attribute_types {0, 0, 0, 0, 0, 0 };
    vector<string> primary_keys {"electricity", "electronics"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_attendees_table() {
    string name = "attendees";
    vector<string> attribute_names {"name", "organization", "address", "email", "registration_fee", "category", "exhibits_visited", "badge_status"};
    vector<int> attribute_types {0, 0, 0, 0, 0, 0, 0, 0};
    vector<string> primary_keys {"name", "organization", "exhibits_visited" , "badge_status"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_inventory_table() {
    string name = "inventory";
    vector<string> attribute_names {"electronics", "furniture"};
    vector<int> attribute_types {0, 0};
    vector<string> primary_keys {"electronics", "furniture"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}



// Exhibitors
void list_exhibitors(bool with_criteria) {
    // If criteria is needed, get it
    string query = "";
    if (with_criteria) {
        string criteria;
        
        // Need to clear out the newline held in cin
        cin.ignore(1,'\n');
        
        cout << "Input your criteria in the grammar of the DML: ";
        getline( cin, criteria );

        if (criteria.length() <= 0) {
            cout << "Warning: Criteria was not given. Proceeding as if it was not required";
            with_criteria = false;
        } else {
            query = "select (" + criteria + ") exhibits;";
            // TODO: Need to check this input for validity and then plug it into a select query
        }
    }
    
    // Fetch proper list of exhibitors and print
    if (with_criteria) {
        char* pch;
        string delimiters = " \",();\n";
        vector<string> command_list;
        
        pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
        while (pch != NULL) {
            command_list.push_back(pch);
            pch = strtok (NULL, delimiters.c_str());
        }
        
        Relation list_relation = interpret_query( rdbms, command_list );
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

void remove_exhibitor() {
    string criteria = "";
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (criteria.length() == 0) {
        cout << "Input your criteria in the grammar of the DML: ";
        getline( cin, criteria );
        
        if (criteria.length() <= 0) {
            cout << "Warning: Criteria was not given!\n";
        } else {
            query = "DELETE FROM exhibits WHERE (" + criteria + ");";
            // TODO: Need to check this input for validity and then plug it into a select query
        }
    }
    
    // Send query to parser
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    query_or_command( rdbms, command_list );
}



// Booths
void register_booth_location() {
    vector<string> fields {"Company name", "Starting row", "Ending row", "Column", "Type(1 for Economy, 2 for Premium)"};
    vector<string> values;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    for (string f : fields) {
        cout << "Please input value for " << f << ": ";
        string input;
        getline( cin, input );
        values.push_back( input );
    }
    
    rdbms.get_relation("booths").insert_tuple( values );
}

void remove_booth_location() {
    string criteria = "";
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (criteria.length() == 0) {
        cout << "Input name of exhibitor company to remove: ";
        getline( cin, criteria );
        
        if (criteria.length() <= 0) {
            cout << "Warning: Criteria was not given!\n";
        } else {
            query = "DELETE FROM booths WHERE (company == \"" + criteria + "\");";
            // TODO: Need to check this input for validity and then plug it into a select query
        }
    }
    
    // Send query to parser
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    query_or_command( rdbms, command_list );
}

void list_booth_locations() {
    string criteria = "";
    string query = "";
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (criteria.length() == 0) {
        cout << "Input name of exhibitor company to find: ";
        getline( cin, criteria );
        
        if (criteria.length() <= 0) {
            cout << "Warning: Criteria was not given!\n";
        } else {
            query = "select (company == \"" + criteria + "\") booths;";
            // TODO: Need to check this input for validity and then plug it into a select query
        }
    }
    
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    Relation list_relation = interpret_query( rdbms, command_list );
    rdbms.app_print_relation( list_relation );
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
    cout << "B1. Assign booth location to exhibitor\n";
    cout << "B2. Delete booth location of exhibitor\n";
    cout << "B3. List booth locations of exhibitor\n";
}

void display_services_menu() {
	cout << "S1. Electricity";
	cout << "S2. Furniture";
	cout << "S3. Electronics";
	cout << "S4. Bar-Code Scanner";
	cout << "S5. Advertisement";
	cout << "S6. Insurance";
}

void display_finance_menu() {
	cout << "F1. Invoice";
	cout << "F2. Revenue";
}

void display_attendees_menu() {
	cout << "A1. Name";
	cout << "A2. Organizations ";
	cout << "A3. Addresses ";
	cout << "A4. E-mails ";
	cout << "A5. Registration Fees ";
	cout << "A6. Categories ";
	cout << "A7. Exhibits visited ";
	cout << "A8. Badge status ";
}
void display_inventory_menu() {
	cout << "I1. Electronics ";
	cout << "I2. Furniture";
}

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
                remove_exhibitor();
                break;
        }
    } else if (command.at(0) == 'B'){
        // Booths menu
		switch (sub_command) {
            case 1:
                register_booth_location();
                break;
                
            case 2:
                remove_booth_location();
                break;
                
            case 3:
                list_booth_locations();
                break;
        }
    } else if (command.at(0) == 'S'){
        // Services menu
	/*	switch (sub_command) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
			case 5:
				break;
			case 6:
				break;
        }	*/
    } else if (command.at(0) == 'F'){
        // Finance menu
    /*    switch (sub_command){
			case 1:
				break;
			case 2:
				break;
		}	*/
    } else if (command.at(0) == 'A'){
        // Attendees menu
	/*	switch (sub_command) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
		}
		
		*/
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
    create_services_table();
    create_attendees_table();
    create_inventory_table();

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
            display_booths_menu();
            // TODO: Fill in rest of applicable menus here
            cout << "Input your command: ";
            
            cin >> next_command;
            stop = interpret_command(next_command);
        } else if (role == EXHIBITOR) {
            display_exhibits_menu();
	
            cout << "Input your command: ";

            cin >> next_command;
	    stop = interpret_command(next_command);

        } else if (role == ATTENDEE) {
            display_attendees_menu();
	    cout << "Input your command; ";

            cin >> next_command;
	    stop = interpret_command(next_command);
        }
    }
	
	return 0;
}
