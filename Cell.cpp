//
//  Cell.cpp
//
#include "Cell.h"

Cell::Cell( int _max_length ){
    max_length = _max_length;
}

Cell::Cell( string data, int _max_length ){
    max_length = _max_length;
    
    if (max_length == 0) {
        int_data = (int)data;
    } else {
        if ( data.length <= max_length )
            string_data = data;
    }
}

bool Cell::is_null(){
    if (string_data.length == 0 && (string)int_data == 0) {
        return true;
    } else {
        return false;
    }
}

auto Cell::get_data(){
    if (max_length == 0){
        return int_data;
    } else {
        return string_data;
    }
}

int Cell::set_value( auto value ){
    if (max_length == 0) {
        int_data = (int)value;
    } else {
        if ( ((string)value).length <= max_length ){
            string_data = (string)value;
            return 0;
        } else {
            return -1;
        }
    }
}