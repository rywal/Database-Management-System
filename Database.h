//This header file will create a class for each 
#include <stdexcept>

class Domain{		//The value of Atrributes

}

class Attribute{	//The column (collection of indexes of Tuples)
//Vector<Domain>       (I'm not sure if this should be a pointer/address)

}

class Tuple{		//The row (fundation of Database)
//Vector<Domain>

}

class Relation {	//Table that holds Columns and rows
//Vector<Attribute<Domain>> (I'm not sure what the type would be.)
//We would have to traverse through the Attribues, first, then we could select which Cell we want, by selecting the Tuple
//I think?


public:
bool doesexist(string att_name){} //Used to see if an Attribute exists
bool compare(string att_name, string compare_string, int index){} //Used to compare a string to each Domain in an Atrribute
int getsize(){} //Used to get the number of Tuples in a Relation
Attribute getatt(int index){} //Used to get Attribute (the data that it connects to) at index
void insert(Tuple &tup_name){} //Used to insert a Tuple into a Relation
void insert(string att_name){} //Used to insert an attribute into the next index of a Relation(possibly union instead??)

}
		
class Database{         //A collection of Tables
	//dynamic data structure for holding different relations
	//a function that creates a new relation

}







