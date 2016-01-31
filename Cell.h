#ifndef Cell_h
#define Cell_h

#include <stdio.h>
#include <string>

// Holds the individual data
class Cell {
private:
    string string_data;
    int int_data;
    int max_length;
    
public:
    Cell( int _max_length );
    Cell( string data, int _max_length );
    bool   is_string(){ return max_length > 0 ? true : false; }
    bool   is_null();
    auto   get_data();
    int    set_value( auto value );
};

#endif /* Cell_h */
