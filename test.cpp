#include <iostream>
#include <stdexcept>
#include <vector>
#include "Relation.h" 
#include "Database.h"
#include "AttributeList.h"
#include "Tuple.h"

void main(){
	Database DB("DB");
	printf ("Create new Relation A:\n");
	string attribute_names1[] = {"Name","ID","ShoeSize", "DogName"};
	int attribute_types1[] = {10, 0, 0, 10};
	string primary_keys_names1[] = {"Name","ID"};
	DB.create_relation("Relation A", attribute_names1, attribute_types1);
	
	string r1_t1[] = {"Jim", "1", "4", "Spot"};
	string r1_t2[] = {"Joe", "2", "6", "Dog"};
	string r1_t3[] = {"Joe", "3", "5", "Spot"};
	
	DB.relation[DB.get_relation_index("Relation A")].insert_tuple(r1_t1);
	DB.relation[DB.get_relation_index("Relation A")].insert_tuple(r1_t2);
	DB.relation[DB.get_relation_index("Relation A")].insert_tuple(r1_t3);
	
	//DB.relation[get_relation_index("Relation A")]
	DB.print_relation("Relation A");
	printf("Select all rows that Name=Joe from Relation A:\n");
	
	std::vector<string> r1_s1 = {"Name"};
	std::vector<string> r1_s2 = {"Joe"};
	std::vector<string> r1_s3 = {"eq"};
	std::vector<string> r1_s4 = {"or"};
	DB.print_relation(select(r1_s1, r1_s2,r1_s3,DB.relation[get_relation_index("Relation A")], r1_s4));
	
	printf("Select all rows that Name=Joe AND DogName=Spot from Relation A:\n");
	std::vector<string> r1_s5 = {"Name","DogName"};
	std::vector<string> r1_s6 = {"Joe","Spot"};
	std::vector<string> r1_s7 = {"eq","eq"};
	std::vector<string> r1_s8 = {"and","and"};
	DB.print_relation(select(r1_s5, r1_s6,r1_s7,DB.relation[get_relation_index("Relation A")], r1_s8));
	
	printf("Select all rows that Name=Joe OR DogName=Spot from Relation A:\n");
	DB.print_relation(select(r1_s5, r1_s6,r1_s7,DB.relation[get_relation_index("Relation A")], r1_s8));
	
	printf("Select Columns \"Name\" and \"DogName\" from Relation A:\n");
	DB.print_relation(project(r1_s5, DB.relation[get_relation_index("Relation A")]));
	
	printf("Rename Attributes \"Name\" to \"Name2\" and \"DogName\" to \"DogName2\" from Relation A:\n");
	std::vector<string> r1_s9 = {"Name2","DogName2"};
	DB.print_relation(renaming("Relation A Renamed", r1_s9, DB.relation[get_relation_index("Relation A")]));
	
	//UPDATE!!!!!
	
	printf ("Create new Relation B:\n");
	DB.create_relation("Relation B", attribute_names1, attribute_types1);
	
	string r1_t4[] = {"Sara", "4", "1", "Riley"};
	string r1_t5[] = {"Suzy", "5", "3", "Puppy"};
	string r1_t6[] = {"Riley", "6", "2", "Animal"};
	
	DB.print_relation("Relation B");
	
	DB.print_relation(set_union("Relation A+B_Union", DB.relation[get_relation_index("Relation A")], DB.relation[get_relation_index("Relation B")]));
	
	
    return 0;
}