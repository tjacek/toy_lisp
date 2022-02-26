#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>
#include <string.h>
#ifndef MATH
#define MATH

enum TokenType {NUMBER,COMMAND,VAR};

const static std::regex ws_reg("\\s+");
const static std::regex number_reg("-?\\d+(\\.\\d+)?");
const static std::regex command_reg("[\\+\\-\\*\\/=()]|set|read|print/");
const static std::regex var_reg("[a-zA-Z][a-zA-Z0-9]*");

class Token{
  public:
    TokenType type;
    virtual std::string to_str()=0;
};

class NumberToken: public Token{
  public:
    double value;
    NumberToken(double value);
    std::string to_str();
};

class StringToken: public Token{
  public:
    std::string value;
    StringToken(TokenType type,std::string value);
    std::string to_str();
};

typedef std::vector<Token*> Line;
Line tokenize(std::string line);
void print_lines(std::vector<Line> & lines);
bool is_token(int i,std::string symbol,Line & line);

enum ASTreeType {SET,READ,PRINT};

class ASTree{
  public:
    ASTreeType type;
    ASTree *left;
    ASTree *right;
};

ASTree * parse_statement(Line & line);

#endif