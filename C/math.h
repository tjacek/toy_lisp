#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <variant>
#include <memory>
#ifndef MATH
#define MATH

enum TokenType {NUMBER,VAR,EQUAL,PLUS,MINUS,DIVIDE,MULT};

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

constexpr const char* type_to_str(TokenType type_i);

class TokenSeq{
  private:
    std::vector<Token*> tokens;
    int current=0;
  
  public:
    void add(Token * token);
    void print();
};

typedef std::shared_ptr<TokenSeq> TokenSeqPtr;
TokenSeqPtr tokenize(std::string line);
void print_lines(std::vector<TokenSeqPtr> & lines);

enum ASTreeType {SET,READ,PRINT};

/*class ASTree{
  public:
    ASTreeType type;
    ASTree *left;
    ASTree *right;
};

ASTree * parse_statement(Line & line);*/

#endif