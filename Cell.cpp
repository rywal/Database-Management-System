//
//  Cell.cpp
//
#include "Cell.h"

Cell::Cell( int _max_length ){
    max_length = _max_length;
}

Cell::Cell(){}

Cell::Cell(Cell a){
	set_value(a.get_dat());
	max_length=a.get_max_length();
}

Cell::Cell( string data, int _max_length ){
    max_length = _max_length;
    
    if (max_length == 0) {
        int_data = (int)data;
    } else {
        if ( data.length() <= max_length )
            string_data = data;
    }
}

int Cell::get_max_length(){
	return max_length;
}
	
bool Cell::is_null(){
    if (string_data.length() == 0 && (string)int_data == 0) {
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


bool Cell::operator==(const Cell &b) const{
	if (max_length==0){
		if (int_data==b.int_data) 
			return true;
	}	
	else if (string_data==b.string_data)
		return true;
	else return false;
}

bool Cell::operator!=(const Cell &b) const{
	if (max_length==0){
                if (int_data==b.int_data) 
                        return false;
        }       
        else if (string_data==b.string_data)
                return false;
        else return true;
} 
