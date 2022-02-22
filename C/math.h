#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>
#ifndef MATH
#define MATH

enum TokenType {NUMBER, SET,READ,PRINT,VAR};

const static std::regex ws_reg("\\s+");
const static std::regex number_reg("-?\\d+(\\.\\d+)?");
const static std::regex command_reg("[\\+\\-\\*\\/=()]|set|read|print/");
const static std::regex var_reg("[a-zA-Z][a-zA-Z0-9]*");


class Token{
  TokenType type;
  double value;

  public:
    Token(double value);
    Token(TokenType type);
};

std::vector<Token> tokenize(std::string line);
#endif