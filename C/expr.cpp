#include "lisp.h"

Atom::Atom(std::string value){
	this->type=ExprType::atom_type;
  this->value=value;
}

void Atom::show(){
	std::cout << this->value <<" ";
}

int Atom::size(){
  return 1;
}

ComplexExpr::ComplexExpr(std::list<Expr*> value){
	this->type=ExprType::complex_type;
  this->value=value;
}

void ComplexExpr::show(){
    std::cout << " " << this->size();
    for(auto it = this->value.begin(); it != this->value.end(); ++it) {
      (*it)->show();
      std::cout <<"\n"; 
    }
}

int ComplexExpr::size(){
    int value=0;
    for(auto it = this->value.begin(); it != this->value.end(); ++it) {
      value+=(*it)->size();
    }
    return value;
}
