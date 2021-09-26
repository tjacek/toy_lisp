#include "lisp.h"

Atom::Atom(std::string value){
	this->value=value;
}

void Atom::show(){
	std::cout << this->value <<" ";
}

int Atom::size(){
  return 1;
}

ProperExpr::ProperExpr(std::list<Expr*> value){
	this->value=value;
}

void ProperExpr::show(){
    std::cout << " " << this->size();
    for(auto it = this->value.begin(); it != this->value.end(); ++it) {
      (*it)->show();
      std::cout <<"\n"; 
    }
}

int ProperExpr::size(){
    int value=0;
    for(auto it = this->value.begin(); it != this->value.end(); ++it) {
      value+=(*it)->size();
    }
    return value;
}
