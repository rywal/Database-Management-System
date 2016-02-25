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
int role = 4; // initialize role to something with no privileges

// Create needed tables
void create_exhibits_table() {
    string name = "exhibits";
    vector<string> attribute_names {"company", "address", "contact", "email", "phone", "fax", "category", "booth_personnel", "description", "website"};
    vector<int> attribute_types {40, 100, 20, 20, 15, 15, 0, 100, 100, 50};
    vector<string> primary_keys {"company"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_booths_table() {
    string name = "booths";
    vector<string> attribute_names {"company", "starting_row", "ending_row", "column", "type"};
    vector<int> attribute_types {40, 0, 0, 0, 0};
    vector<string> primary_keys {"company", "starting_row", "ending_row", "column"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_services_table() {
    string name = "services";
    vector<string> attribute_names {"exhibitor", "inventory_key", "price"};
    vector<int> attribute_types {40, 20, 0};
    vector<string> primary_keys {"exhibitor", "inventory_key"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_attendees_table() {
    string name = "attendees";
    vector<string> attribute_names {"name", "organization", "address", "email", "registration_fee", "category", "badge_status"};
    vector<int> attribute_types {40, 40, 100, 25, 0, 0, 0};
    vector<string> primary_keys {"name", "organization", "badge_status"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_exhibits_visited_table() {
    string name = "exhibits_visited";
    vector<string> attribute_names {"attendee", "exhibitor"};
    vector<int> attribute_types {40, 40};
    vector<string> primary_keys {"attendee"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
}

void create_inventory_table() {
    string name = "inventory";
    vector<string> attribute_names {"key", "description", "price", "quantity"};
    vector<int> attribute_types {20, 100, 0, 0};
    vector<string> primary_keys {"key"};
    
    rdbms.create_relation(name, attribute_names, attribute_types, primary_keys);
    
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"e500", "Electricity (500W)", "30", "999"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"e1000", "Electricity(1000W)", "40", "999"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"e1500", "Electricity(1500W)", "50", "999"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"table1", "Table of size 1", "25", "5"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"table2", "Table of size 2", "25", "5"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"table3", "Table of size 3", "30", "5"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"table4", "Table of size 4", "30", "5"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"table5", "Table of size 5", "35", "5"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"chair", "Chair", "10", "100"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"fstv", "Flatscreen TV", "60", "25"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"cm", "Computer Monitor", "25", "15"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"laptop", "Laptop computer", "90", "35"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"projector", "Projector", "28", "15"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"projectorscreen", "Projector Screen", "10", "15"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"scanner", "Barcode Scanner", "5", "40"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ad1", "Exhibitor Guide", "60", "10"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ad2", "Online exhibitor guide", "40", "55"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ad3", "Large banner", "32", "15"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ad4", "Small banner", "27", "25"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ins1", "Insurance Coverage: $1 million", "10000", "10"});
    rdbms.get_relation("inventory").insert_tuple(vector<string>{"ins2", "Insurance Coverage: $10 million", "400000", "10"});
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



// Attendees
void add_to_visited_list(string a, string e) {
    string attendee = a;
    string exhibitor = e;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (attendee.length() == 0) {
        cout << "Input name of attendee: ";
        getline( cin, attendee );
        
        if (attendee.length() <= 0)
            cout << "Error: Input was not given!\n";
    }
    
    while (exhibitor.length() == 0) {
        cout << "Input name of exhibitor company: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0)
            cout << "Error: Input was not given!\n";
    }
    
    vector<string> values{attendee, exhibitor};
    rdbms.get_relation("exhibits_visited").insert_tuple( values );
}

void remove_from_visited_list(string a, string e) {
    string attendee = a;
    string exhibitor = e;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (attendee.length() == 0) {
        cout << "Input name of attendee: ";
        getline( cin, attendee );
        
        if (attendee.length() <= 0)
            cout << "Error: Input was not given!\n";
    }
    
    while (exhibitor.length() == 0) {
        cout << "Input name of exhibitor company: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0)
            cout << "Error: Input was not given!\n";
    }
    
    // Send query to parser
    string query = "DELETE FROM exhibits_visited WHERE (exhibitor == " + exhibitor + " && attendee == " + attendee + ");";
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

void list_visited_list(string e) {
    string exhibitor = e;
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (exhibitor.length() == 0) {
        cout << "Input name of exhibitor company to list from: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0) {
            cout << "Error: Input was not given!\n";
        }
    }
    
    // Assemble query and send to interpret
    string query = "select (exhibitor == \"" + exhibitor + "\") exhibits_visited;";
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

void list_attendees(bool with_criteria) {
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
            query = "select (" + criteria + ") attendees;";
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
        Relation list_relation = rdbms.get_relation("attendees");
        rdbms.app_print_relation( list_relation );
    }
}

void register_attendee() {
    vector<string> fields {"name", "organization", "address", "email", "registration_fee", "category", "badge_status"};
    vector<string> values;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    for (string f : fields) {
        cout << "Please input value for " << f << ": ";
        string input;
        getline( cin, input );
        values.push_back( input );
    }
    
    rdbms.get_relation("attendees").insert_tuple( values );
}

void remove_attendee() {
    string criteria = "";
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (criteria.length() == 0) {
        cout << "Input name of attendee to remove: ";
        getline( cin, criteria );
        
        if (criteria.length() <= 0) {
            cout << "Warning: Name was not given!\n";
        } else {
            query = "DELETE FROM attendees WHERE (name == " + criteria + ");";
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



// Services
bool item_in_stock(string key) {
    string query = "select (key == " + key + ") inventory;";
    
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    Relation inventory_rel = interpret_query( rdbms, command_list );
    
    if (inventory_rel.get_size() > 0) {
        int quantity = std::stoi( inventory_rel.tuples[0].get_cell(3).get_data() );
        cout << "Item with key " << key << " found to have " << quantity << " quantity\n";
        if (quantity > 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void decrement_stock(string key){
    string query = "select (key == " + key + ") inventory;";
    
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    int quantity = 0;
    Relation inventory_rel = interpret_query( rdbms, command_list );
    
    if (inventory_rel.get_size() > 0) {
        quantity = std::stoi( inventory_rel.tuples[0].get_cell(3).get_data() );
        cout << "Item with key " << key << " found to have " << quantity << " quantity\n";
    } else {
        cout << "No item found with key " << key << "\n";
        return;
    }
    
    query = "UPDATE inventory SET (quantity = " + std::to_string(quantity-1) + ") WHERE (key == " + key + ");";
    // Send query to parser
    char* pchu;
    vector<string> command_list_update;
    
    pchu = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pchu != NULL) {
        command_list_update.push_back(pchu);
        pchu = strtok (NULL, delimiters.c_str());
    }
    
    query_or_command( rdbms, command_list_update );
}

void increment_stock(string key){
    string query = "select (key == " + key + ") inventory;";
    
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    int quantity = 0;
    Relation inventory_rel = interpret_query( rdbms, command_list );
    
    if (inventory_rel.get_size() > 0) {
        quantity = std::stoi( inventory_rel.tuples[0].get_cell(3).get_data() );
        cout << "Item with key " << key << " found to have " << quantity << " quantity\n";
    } else {
        cout << "No item found with key " << key << "\n";
        return;
    }
    
    query = "UPDATE inventory SET (quantity = " + std::to_string(quantity+1) + ")  WHERE (key == " + key + ");";
    // Send query to parser
    char* pchu;
    vector<string> command_list_update;
    
    pchu = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pchu != NULL) {
        command_list_update.push_back(pchu);
        pchu = strtok (NULL, delimiters.c_str());
    }
    
    query_or_command( rdbms, command_list_update );
}

void assign_service_to_exhibitor(string e) {
    string exhibitor = e;
    string key = "";
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (exhibitor.length() == 0) {
        cout << "Input company name of exhibitor: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0) {
            cout << "Warning: Exhibitor company was not given!\n";
        }
    }
    
    while (key.length() == 0) {
        cout << "Input name of key in inventory: ";
        getline( cin, key );
        
        if (key.length() <= 0) {
            cout << "Warning: Key was not given!\n";
        }
    }
    
    if ( item_in_stock(key) ) {
        // Service/Item is in stock. Let's add it here and decrement the quantity available
        query = "select (key == " + key + ") inventory;";
        
        char* pch;
        string delimiters = " \",();\n";
        vector<string> command_list;
        
        pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
        while (pch != NULL) {
            command_list.push_back(pch);
            pch = strtok (NULL, delimiters.c_str());
        }
        
        Relation inventory_rel = interpret_query( rdbms, command_list );
        
        vector<string> values;
        if (inventory_rel.get_size() > 0) {
            values.push_back( exhibitor ); // Add exhibitor
            values.push_back( inventory_rel.tuples[0].get_cell(0).get_data() ); // Add key
            values.push_back( inventory_rel.tuples[0].get_cell(2).get_data() ); // Add price
        }
        
        rdbms.get_relation("services").insert_tuple(values);
        
        decrement_stock( key );
    } else {
        cout << "The item with that key is no longer in stock!\n";
    }
}

void remove_service_from_exhibitor(string e) {
    string exhibitor = e;
    string key = "";
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (exhibitor.length() == 0) {
        cout << "Input company name of exhibitor: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0) {
            cout << "Warning: Exhibitor company was not given!\n";
        }
    }
    
    while (key.length() == 0) {
        cout << "Input name of key in inventory: ";
        getline( cin, key );
        
        if (key.length() <= 0) {
            cout << "Warning: Key was not given!\n";
        }
    }
    
    // Service/Item is in stock. Let's add it here and decrement the quantity available
    query = "DELETE FROM services WHERE (inventory_key == " + key + ");";
    
    char* pch;
    string delimiters = " \",();\n";
    vector<string> command_list;
    
    pch = strtok ((char*)query.c_str(), delimiters.c_str());//Lexer
    while (pch != NULL) {
        command_list.push_back(pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    query_or_command( rdbms, command_list );
    
    increment_stock( key );
}

void list_services_for_exhibitor(string e) {
    // If exhibit is needed, get it
    string exhibitor = e;
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (exhibitor.length() == 0) {
        cout << "Input company of exhibitor to show services for: ";
        getline( cin, exhibitor );
        
        if (exhibitor.length() <= 0) {
            cout << "Warning: Exhibitor company name was not given!\n";
        }
    }
    
    query = "select (exhibitor == " + exhibitor + ") services;";
    
    // Fetch proper list of exhibitors and print
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



// Inventory
void list_inventory(bool with_criteria) {
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
            query = "select (" + criteria + ") inventory;";
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
        Relation list_relation = rdbms.get_relation("inventory");
        rdbms.app_print_relation( list_relation );
    }
}

void add_to_inventory() {
    vector<string> fields {"Key", "Description", "Price(Integer)", "Quantity(Integer)"};
    vector<string> values;
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    for (string f : fields) {
        cout << "Please input value for " << f << ": ";
        string input;
        getline( cin, input );
        values.push_back( input );
    }
    
    rdbms.get_relation("inventory").insert_tuple( values );
}

void remove_from_inventory(string k) {
    string key = k;
    string query = "";
    
    // Need to clear out the newline held in cin
    cin.ignore(1,'\n');
    
    while (key.length() == 0) {
        cout << "Input key to remove: ";
        getline( cin, key );
        
        if (key.length() <= 0) {
            cout << "Warning: Key was not given!\n";
        } else {
            query = "DELETE FROM inventory WHERE (key == " + key + ");";
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
    cout << "\nServices\n";
    cout << "----------\n";
	cout << "S1. Assign services to exhibitor\n";
	cout << "S2. Remove services from exhibitor\n";
	cout << "S3. List services for exhibitor\n";
}

void display_finance_menu() {
    cout << "\nFinance\n";
    cout << "----------\n";
	cout << "F1. Show invoice for exhibitor\n";
	cout << "F2. Show total revenue\n";
}

void display_attendees_menu() {
    cout << "\nAttendees\n";
    cout << "----------\n";
	cout << "A1. Add attendee to exhibit's visited list\n";
	cout << "A2. Remove attendee from exhibit's visited list\n";
    cout << "A3. Show attendees who visited an exhibit\n";
    cout << "A4. List attendees\n";
	cout << "A5. Register new attendee\n";
	cout << "A6. Remove attendee\n";
	cout << "A7. Search attendees based on criteria\n";
}
void display_inventory_menu() {
    cout << "\nInventory\n";
    cout << "----------\n";
	cout << "I1. Add to inventory\n";
	cout << "I2. Remove from inventory\n";
    cout << "I3. List inventory\n";
}

// Intepret the given command
bool interpret_command(string command){
    system("clear");
    if (command.at(0) == 'Q' || command.length() < 2) {
        // Quit command given
        return true;
    }
    
    // Get the second character in the given command
    int sub_command = command.at(1) - '0';
    
    // Quit command not given, continue parsing
    if (command.at(0) == 'E') {
        // Exhibits menu
        switch (sub_command) {
            case 1: // E1. List Exhibitors
                list_exhibitors(false);
                break;
                
            case 2: // E2. List Exhibitors(based on criteria)
                list_exhibitors(true);
                break;
                
            case 3: // E3. Register new Exhibitor
                register_exhibitor();
                break;
                
            case 4: // E4. Remove Exhibitor(s)
                remove_exhibitor();
                break;
        }
    } else if (command.at(0) == 'B'){
        // Booths menu
        switch (sub_command) {
            case 1: // B1. Assign booth location to exhibitor
                register_booth_location();
                break;
                
            case 2: // B2. Delete booth location of exhibitor
                remove_booth_location();
                break;
                
            case 3: // B3. List booth locations of exhibitor
                list_booth_locations();
                break;
        }
    } else if (command.at(0) == 'S'){
        // Services menu
		switch (sub_command) {
            case 1: // S1. Assign services to exhibitor
                assign_service_to_exhibitor("");
                break;
            case 2: // S2. Remove services from exhibitor
                remove_service_from_exhibitor("");
                break;
            case 3: // S3. List services for exhibitor
                list_services_for_exhibitor("");
                break;
        }
    } else if (command.at(0) == 'F'){
        // Finance menu
        switch (sub_command){
			case 1: // F1. Show invoice for exhibitor
				break;
			case 2: // F2. Show total revenue
				break;
		}
    } else if (command.at(0) == 'A'){
        // Attendees menu
        switch (sub_command) {
			case 1: // A1. Add attendee to exhibit's visited list
                add_to_visited_list("", "");
				break;
			case 2: // A2. Remove attendee from exhibit's visited list
                remove_from_visited_list("", "");
				break;
			case 3: // A3. Show attendees who visited an exhibit
                list_visited_list("");
				break;
			case 4: // A4. List attendees
                list_attendees(false);
				break;
			case 5: // A5. Register new attendee
                register_attendee();
				break;
			case 6: // A6. Remove attendee
                remove_attendee();
				break;
			case 7: // A7. Search attendees based on criteria
                list_attendees(true);
				break;
		}
    } else if (command.at(0) == 'I'){
        // Inventory menu
        switch (sub_command) {
            case 1: // I1. Add to inventory
                add_to_inventory();
                break;
            case 2: // I2. Remove from inventory
                remove_from_inventory("");
                break;
            case 3: // I3. List inventory
                list_inventory(false);
                break;
                
        }
    } else {
        // Command not found
        cout << "Command '" << command << "' not found.\n";
        return true;
    }
    
    return false;
}

void get_user_role() {
    while (role < 0 || role > 3) {
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
                break;
            default:
                role = -1;
                cout << "ERROR: Please enter input based on the instructions\n";
                break;
        }
    }
}

int main(){
    create_exhibits_table();
    create_booths_table();
    create_services_table();
    create_attendees_table();
    create_exhibits_visited_table();
    create_inventory_table();

    // TODO: Add in the rest of the create functions
    // create_NAME_table();
    
    // Find user's role
    get_user_role();
    if (role == 4) {
        return 0;
    }
    
    // Display menus based on user's role
    string next_command = "";
    bool stop = false;
    while (!stop) {
        if (role == EXHIBIT_MANAGER){
            cout << "---------------------------------\n";
            cout << "-           Main Menu           -\n";
            cout << "-        Exhibit Manager        -\n";
            cout << "---------------------------------\n";
            display_exhibits_menu();
            display_booths_menu();
            display_services_menu();
            display_finance_menu();
            display_attendees_menu();
            display_inventory_menu();
            cout << "Input your command: ";
            
            cin >> next_command;
            stop = interpret_command(next_command);
        } else if (role == EXHIBITOR) {
            cout << "---------------------------------\n";
            cout << "-           Main Menu           -\n";
            cout << "-           Exhibitor           -\n";
            cout << "---------------------------------\n";
            display_exhibits_menu();
	
            cout << "Input your command: ";

            cin >> next_command;
	    	stop = interpret_command(next_command);
        } else if (role == ATTENDEE) {
            cout << "---------------------------------\n";
            cout << "-           Main Menu           -\n";
            cout << "-           Attendees           -\n";
            cout << "---------------------------------\n";
            display_attendees_menu();
	    	cout << "Input your command; ";

            cin >> next_command;
	    	stop = interpret_command(next_command);
        }
    }
	
	return 0;
}
