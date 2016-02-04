#include <iostream>
#include <stdexcept>
#include <vector>
#include "Relation.h" 
#include "Database.h"
#include "AttributeList.h"
#include "Tuple.h"

int main(){
	Database DB("DB");
	printf ("Create new Relation A:\n");
	string attribute_names1[] = {"Name","ID","ShoeSize", "DogName"};
	int attribute_types1[] = {10, 0, 0, 10};
    vector<string> primary_keys_names1;
    primary_keys_names1.push_back("Name");
    primary_keys_names1.push_back("ID");
    
	DB.create_relation("Relation A", attribute_names1, attribute_types1, primary_keys_names1);
	
	string r1_t1[] = {"Jim", "1", "4", "Spot"};
	string r1_t2[] = {"Joe", "2", "6", "Dog"};
	string r1_t3[] = {"Joe", "3", "5", "Spot"};
	
	DB.get_relation("Relation A").insert_tuple(r1_t1);
	DB.get_relation("Relation A").insert_tuple(r1_t2);
	DB.get_relation("Relation A").insert_tuple(r1_t3);
	
	//DB.relation[get_relation_index("Relation A")]
	DB.print_relation("Relation A");
	printf("Select all rows that Name=Joe from Relation A:\n");
	
    std::vector<string> r1_s1;
    r1_s1.push_back("Name");
    std::vector<string> r1_s2;
    r1_s1.push_back("Joe";
    std::vector<string> r1_s3;
    r1_s1.push_back("eq");
    std::vector<string> r1_s4;
    r1_s1.push_back("or");
	DB.print_relation(DB.select(r1_s1, r1_s2,r1_s3,DB.get_relation("Relation A"), r1_s4));
	
	printf("Select all rows that Name=Joe AND DogName=Spot from Relation A:\n");
    std::vector<string> r1_s5, r1_s6, r1_s7, r1_s8;
    r1_s5.push_back("Name");
    r1_s5.push_back("DogName");
    r1_s6.push_back("Joe");
    r1_s6.push_back("Spot");
    r1_s7.push_back("eq");
    r1_s7.push_back("eq");
    r1_s8.push_back("and");
    r1_s8.push_back("and");
	DB.print_relation(DB.select(r1_s5, r1_s6,r1_s7,DB.get_relation("Relation A"), r1_s8));
	
	printf("Select all rows that Name=Joe OR DogName=Spot from Relation A:\n");
	DB.print_relation(DB.select(r1_s5, r1_s6,r1_s7,DB.get_relation("Relation A"), r1_s8));
	
	printf("Select Columns \"Name\" and \"DogName\" from Relation A:\n");
	DB.print_relation(DB.project(r1_s5, DB.get_relation("Relation A")));
	
	printf("Rename Attributes \"Name\" to \"Name2\" and \"DogName\" to \"DogName2\" from Relation A:\n");
	std::vector<string> r1_s9 = {"Name2","DogName2"};
	DB.print_relation(DB.renaming("Relation A Renamed", r1_s9, DB.get_relation("Relation A")));
	
	//UPDATE!!!!!
	
	printf ("Create new Relation B:\n");
	DB.create_relation("Relation B", attribute_names1, attribute_types1, primary_keys_names1);
	
	string r1_t4[] = {"Sara", "4", "1", "Riley"};
	string r1_t5[] = {"Suzy", "5", "3", "Puppy"};
	string r1_t6[] = {"Riley", "6", "2", "Animal"};
	
	DB.get_relation("Relation B").insert_tuple(r1_t4);
	DB.get_relation("Relation B").insert_tuple(r1_t5);
	DB.get_relation("Relation B").insert_tuple(r1_t6);
	
	DB.print_relation("Relation B");
	
    printf ("Union Relation A & Relation B:\n");
    DB.print_relation(DB.set_union("Relation A+B_Union", DB.get_relation("Relation A"), DB.get_relation("Relation B")));
	
	DB.create_relation("Relation C", attribute_names1, attribute_types1, primary_keys_names1);
	
	string r1_t7[] = {"Jim", "1", "4", "Spot"};
	string r1_t8[] = {"Bob", "2", "6", "Dog"};
	string r1_t9[] = {"Joe", "4", "5", "Spot"};
	
	DB.get_relation("Relation C").insert_tuple(r1_t7);
	DB.get_relation("Relation C").insert_tuple(r1_t8);
	DB.get_relation("Relation C").insert_tuple(r1_t9);
	
	printf ("Set Difference of Relation A & Relation B:\n");
	DB.print_relation(DB.set_difference("Relation A-B_Difference", DB.get_relation("Relation A"), DB.get_relation("Relation B")));
	
    return 0;
}