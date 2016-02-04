#ifndef Cell_h
#define Cell_h

#include <stdio.h>
#include <string>

using namespace std;
// Holds the individual data
class Cell {
private:
    string string_data;
    int int_data;
    int max_length;
    
public:
    Cell( int _max_length );
    Cell();
    Cell(Cell a);
    Cell( string data, int _max_length );
    bool   is_string(){ return max_length > 0 ? true : false; }
    bool   is_null();
    int	   get_max_length();
    auto   get_data();
    int    set_value( string value );

    bool operator==(const Cell &b) const;
    bool operator!=(const Cell &b) const;

};

#endif /* Cell_h */
