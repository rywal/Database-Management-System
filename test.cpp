/*#include <iostream>
#include <stdexcept>
#include <vector>
#include "Relation.h" 
#include "Database.h"
#include "AttributeList.h"
#include "Tuple.h"

int main(){
	Database DB("DB");
	printf ("Create new Relation A:\n");
	std::vector<string> attribute_names1 = {"Name","ID","ShoeSize", "DogName"};
    std::vector<int> attribute_types1 = {10, 0, 0, 10};

    std::vector<string> primary_keys_names1 = {"Name", "ID"};
	DB.create_relation("Relation A", attribute_names1, attribute_types1, primary_keys_names1);
    
    Relation relA = DB.get_relation("Relation A");
	
    std::vector<string> r1_t1 = {"Joe", "1", "4", "Spot"};
    std::vector<string> r1_t2 = {"Bob", "2", "5", "Spike"};
    std::vector<string> r1_t3 = {"Jim", "3", "6", "Spike"};
    std::vector<string> r1_t0 = {"Joe", "6", "9", "Spot"};
	
	relA.insert_tuple(r1_t1);
	relA.insert_tuple(r1_t2);
    relA.insert_tuple(r1_t3);
    relA.insert_tuple(r1_t0);
    
//	cout<<"1\n";	
	DB.print_relation(relA);
	printf("Select all rows that Name=Joe from Relation A:\n");
//	cout<<"5\n";
    Relation query = DB.select("Name", "Joe", "eq", relA);
//	cout<<"6\n";
	DB.print_relation(query);
//	cout<<"3\n";	
	printf("Select all rows that Name=Joe AND DogName=Spot from Relation A:\n");
    
    query = DB.select("Name", "Joe", "eq", relA);
    query = DB.select("DogName", "Spot", "eq", query);
    DB.print_relation(query);
    
	printf("Select all rows that Name=Joe OR DogName=Spike from Relation A:\n");
    Relation queryA = DB.select("Name", "Joe", "eq", relA);
    Relation queryB = DB.select("DogName", "Spike", "eq", relA);
    Relation queryC = DB.set_union("Name=Joe OR DogName=Spike", queryA, queryB);
	DB.print_relation(queryC);
	
    
    std::vector<string> r1_s5;
    r1_s5.push_back("Name");
    r1_s5.push_back("DogName");
	printf("Project Columns \"Name\" and \"DogName\" from Relation A:\n");
    query = DB.project(r1_s5, relA);
	DB.print_relation(query);
	
	printf("Rename Attributes \"Name\" to \"Name2\" and \"DogName\" to \"DogName2\" from Relation A:\n");
	std::vector<string> r1_s9;
	r1_s9.push_back("Name2");
    r1_s9.push_back("DogName3");
	
    query = DB.renaming("Relation A Renamed", r1_s9, query);
	DB.print_relation(query);
	
	//UPDATE!!!!!
	
	printf ("Create new Relation B:\n");
	DB.create_relation("Relation B", attribute_names1, attribute_types1, primary_keys_names1);
    Relation relB = DB.get_relation("Relation B");
    
    std::vector<string> r1_t4 = {"sara", "4", "1", "Riley"};
    std::vector<string> r1_t5 = {"Suzy", "5", "3", "Puppy"};
    std::vector<string> r1_t6 = {"Riley", "6", "2", "animal"};
	
	relB.insert_tuple(r1_t4);
	relB.insert_tuple(r1_t5);
	relB.insert_tuple(r1_t6);
	
	DB.print_relation(relB);
	
    printf ("Union Relation A & Relation B:\n");
    query = DB.set_union("Relation A+B_Union", relA, relB);
    DB.print_relation(query);
	
	DB.create_relation("Relation C", attribute_names1, attribute_types1, primary_keys_names1);
    Relation relC = DB.get_relation("Relation C");
	
	std::vector<string> r1_t7 = {"Jim", "1", "4", "Spot"};
    std::vector<string> r1_t8 = {"Bob", "2", "6", "Dog"};
    std::vector<string> r1_t9 = {"Joe", "4", "5", "Spot"};
	
	relC.insert_tuple(r1_t7);
	relC.insert_tuple(r1_t8);
	relC.insert_tuple(r1_t9);

	printf ("Set Difference of Relation A & Relation B:\n");
    query = DB.set_difference("Relation A-B_Difference", relA, relB);
	DB.print_relation(query);

	std::vector<string> attribute_names2 = {"CatName","Believingness"};
    std::vector<int> attribute_types2 = {10, 0};
    std::vector<string> primary_keys_names2 = {"Believingness"};
	
	DB.create_relation("Relation D", attribute_names2, attribute_types2, primary_keys_names2);
    Relation relD = DB.get_relation("Relation D");
	
    std::vector<string> r2_t1 = {"Cat", "1"};
    std::vector<string> r2_t2 = {"Dog", "2"};
    std::vector<string> r2_t3 = {"Bird", "3"};
	
	relD.insert_tuple(r2_t1);
	relD.insert_tuple(r2_t2);
	relD.insert_tuple(r2_t3);
	
    printf ("BEFORE: Update Cat -> Kitten:\n");
	DB.print_relation(relD);
    
    printf ("After: Update Cat -> Kitten:\n");
    void update(Relation &in_rel, string att_name, string compare_operator, string comparison_value, string update_name);
    DB.update(relD, "CatName", "eq", "Cat", "Kitten");
    DB.print_relation(relD);
    
    relD.insert_tuple(r2_t3);
    
    printf ("Cross Product of A & D:\n");
    query = DB.cross_product("Relation A-D_CrossProduct", relA, relD);
    DB.print_relation(query);
	
    return 0;
}*/
