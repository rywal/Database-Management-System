//
//  ryan_parser.cpp
//  
//
//  Created by Ryan Walters on 2/15/16.
//
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include "Database.h"

bool interpret_create(Database &db, std::vector<std::string> command) {
    if (command.size() > 5) {
        string relation_name = command[0];
        
        string next_token = command[1];
        bool column_name_just_found = false;
        std::vector<std::string> attribute_names;
        std::vector<int> attribute_sizes;
        std::vector<std::string> primary_keys;
        
        for (int i = 1; i < command.size(); i++){
            if (command[i] == "PRIMARY")
                break;
            
            if (!column_name_just_found) {
                attribute_names.push_back( command[i] );
                std::cout << "Attribute found with name: " << command[i];
                column_name_just_found = true;
            } else {
                if (command[i] == "VARCHAR") {
                    i++;
                    std::string::size_type sz;
                    int attribute_size = std::stoi (command[i], &sz);
                    attribute_sizes.push_back( attribute_size );
                    std::cout << " Inserting with size: " << attribute_size << std::endl;
                } else if(command[i] == "INTEGER") {
                    attribute_sizes.push_back(0);
                    std::cout << " Inserting with size: 0" << std::endl;
                }
                
                column_name_just_found = false;
            }
        }
        
    } else {
        std::cout << "Not enough tokens given to interpret a create statement" << std::endl;
    }
}

void interpret_command(Database &db, std::vector<std::string> command) {
    if (command[0] == "CREATE") {
        if (command.size() > 2 && command[1] == "TABLE") {
            command.erase (command.begin(), command.begin()+2);
            std::vector<std::string> rest_of_commands = command;
            interpret_create(db, rest_of_commands);
        } else {
            std::cout << "Error parsing your command - either not enough tokens or 'TABLE' not found" << std::endl;
        }
    } else {
        std::cout << "Error parsing your command" << std::endl;
    }
}

int main() {
    Database db("db");
    char str[] = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
    char * pch;
    std::string delimiters = " ,();";
    printf ("Splitting string \"%s\" into tokens:\n",str);
    std::vector<std::string> current_command;
    pch = strtok (str, delimiters.c_str());
    while (pch != NULL) {
        current_command.push_back(pch);
        printf ("%s\n",pch);
        pch = strtok (NULL, delimiters.c_str());
    }
    
    interpret_command(db, current_command);
    
    return 0;
}