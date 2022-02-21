#include "math.h"
  
Token::Token(double value){
  this->type=NUMBER;
  this->value=value;
}

Token::Token(TokenType type){
	this->type=type;
	this->value=0.0;
}

int main(){
  Token a(5.0);
}