#include <iostream>
#include <stdexcept>
#include <vector>
#include "Relation.h" 
#include "Database.h"
#include "AttributeList.h"
#include "Tuple.h"

void main(){
<<<<<<< HEAD
	Database DB("DB");
	printf ("Create new Relation A:\n");
=======
	//Create Relation
	Database DB("DB");
>>>>>>> 41de14dcf9fccdde9ddb8ba06d629f745ae55503
	string attribute_names1[] = {"Name","ID","ShoeSize", "DogName"};
	int attribute_types1[] = {10, 0, 0, 10};
	string primary_keys_names1[] = {"Name","ID"};
	DB.create_relation("Relation A", attribute_names1, attribute_types1);
<<<<<<< HEAD
	
	//DB.relation[get_relation_index("Relation A")]
	DB.print_relation("Relation A");
	printf("Select Relation A with all rows that ha")
	printf ("Create new Relation B:\n");
	
=======
	DB.relation("Relation A");
>>>>>>> 41de14dcf9fccdde9ddb8ba06d629f745ae55503

}