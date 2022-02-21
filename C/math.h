#include <string>
#include <iostream>
#include <regex>
#include <list>
#ifndef MATH
#define MATH

enum TokenType {NUMBER, SET,READ,PRINT,VAR};

class Token{
  TokenType type;
  double value;

  public:
    Token(double value);
    Token(TokenType type);
};

#endif