#include <iostream>
#include <vector>
#include <sstream>

struct atomic-expr : public Expr{		//atomic-expr is a member of the parent class Expr
	
	Atomic-expr(Relation-name rn, Expr e);	//Releation name is another class
	Relation-name table;
	Expr expression;
	
	
//	Expr funtions redefined here

}

