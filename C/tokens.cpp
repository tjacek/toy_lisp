#include "tokens.h"

Token::Token(TokenType type,std::string str){
  this->type=VAR;
  this->data=str;
}