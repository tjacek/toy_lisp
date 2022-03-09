#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>
#include <variant>
#ifndef MATH
#define MATH

enum TokenType {NUMBER,VAR};

const static std::regex ws_reg("\\s+");
const static std::regex number_reg("-?\\d+(\\.\\d+)?");
const static std::regex command_reg("[\\+\\-\\*\\/=()]|set|read|print/");
const static std::regex var_reg("[a-zA-Z][a-zA-Z0-9]*");

class Token{
  public:
    TokenType type;
    std::variant<std::string,float> data;
    Token(std::string str);
    Token(float n);
    Token(TokenType type);
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