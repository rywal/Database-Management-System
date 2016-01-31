#include <stdexcept>
#include <vector>

// Core Database Components
// ------------------------
// Created by: Ryan Walters, Jonathan Grimes, Nathan Blattman and Victor Vazquez
// Outlines the various components of the Core Database functionality

// A collection of tables
class Database {
    string name;
    std::vector<Relation> relations;
    
    Database(string name);
};