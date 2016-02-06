#include <iostream>
#include <vector>
#include <sstream>

struct Query{

	Query(Relation-name n, Expr e);
	
	Relation-name 

};

struct Relation-name{

	Relation-name(Identifier I);
	
	Identifier ID;
};

struct Identifier{
	
	Identifier(Alpha a, Alpha b);
	Identifier(Alpha a, Digit b);

	Alpha first;
	Alpha second;
};

struct Digit{

	Digit (int a);
	
	int digit;
	bool valid_Digit();
};

struct Alpha{

	Alpha (char a);
	
	char alpha;
	bool valid_Alpha(); 
};

struct Expr{

	Expr();
	
};

struct atomic-expr : public Expr{		//atomic-expr is a member of the parent class Expr
	
	Atomic-expr(Relation-name rn, Expr e);	//Releation name is another class
	Relation-name table;
	Expr expression;
	
	
//	Expr funtions redefined here

};

struct Renaming : public Expr{

	
}

struct Selection : public Expr{

};

struct Projection : public Expr{

};

struct Union : public Expr{

};

struct Difference : public Expr{

};

struct Product : public Expr{

};

struct Attribute-list{

};

struct Attribute-name{

};

struct Condition{

};

struct Conjunction{

};

struct Comparison{

};

struct Op{

};

struct Operand{

};

struct Literal{

};

