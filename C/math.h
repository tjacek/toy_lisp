#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>
#ifndef MATH
#define MATH

enum TokenType {NUMBER, SET,READ,PRINT,VAR};

const static std::regex ws("\\s+");

class Token{
  TokenType type;
  double value;

  public:
    Token(double value);
    Token(TokenType type);
};

std::vector<Token> tokenize(std::string line);
#endif