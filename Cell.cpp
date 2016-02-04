//
//  Cell.cpp
//
#include <iostream>
#include "Cell.h"

Cell::Cell( int _max_length ){
    max_length = _max_length;
}

Cell::Cell(){}

Cell::Cell(Cell &a){
    max_length=a.get_max_length();
	set_value(a.get_data());
}

Cell::Cell( string data, int _max_length ){
    max_length = _max_length;
    std::cout << "data: " << data << " max_length: " << max_length << std::endl;
    
    if (max_length == 0) {
        int_data = std::stoi(data.c_str());
    } else {
        if ( data.length() <= max_length )
            string_data = data;
    }
}

int Cell::get_max_length(){
	return max_length;
}
	
bool Cell::is_null(){
    if (string_data.length() == 0 && std::to_string(int_data).length() == 0) {
        return true;
    } else {
        return false;
    }
}

string Cell::get_data(){
    if (max_length == 0){
        return std::to_string(int_data);
    } else {
        return string_data;
    }
}

int Cell::set_value( string value ){
    if (max_length == 0) {
        std::cout << "Trying to set value of " << value << "\n";
        int_data = std::stoi(value.c_str());
    } else {
        if ( value.length() <= max_length ){
            string_data = value;
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
