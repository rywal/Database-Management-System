#include <iostream>
#include <stdexcept>
#include <vector>
#include "Relation.h" 
#include "Database.h"
#include "AttributeList.h"
#include "Tuple.h"

void main(){
	//Create Relation
	Database DB("DB");
	string attribute_names1[] = {"Name","ID","ShoeSize", "DogName"};
	int attribute_types1[] = {10, 0, 0, 10};
	string primary_keys_names1[] = {"Name","ID"};
	DB.create_relation("Relation A", attribute_names1, attribute_types1);
	DB.relation("Relation A"]

}