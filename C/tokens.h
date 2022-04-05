#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <memory>
#include <algorithm>
#ifndef MATH
#define MATH

enum TokenType {SYNTAX,NUMBER,VAR,STRING};

const static std::regex ws_reg("\\s+");
const static std::regex number_reg("-?\\d+(\\.\\d+)?");
const static std::regex command_reg("[\\+\\-\\*\\/=()]|lambda|define");
const static std::regex var_reg("[a-zA-Z][a-zA-Z0-9\\-]*");

class Token{
  public:
    TokenType type;
    std::string data;
    Token(TokenType type,std::string str);
    std::string get_type();
};

typedef std::shared_ptr<Token> TokenPtr;

class TokenSeq{
  private:
    std::vector<TokenPtr> tokens;
    int current=0;

  public:
  	void add(TokenPtr token);
  	void print(int start=0);
  	void print_types();
};

typedef std::shared_ptr<TokenSeq> TokenSeqPtr;
TokenSeqPtr tokenize(std::string line);
void replace_string(std::string& subject, const std::string& search,
	const std::string& replace);
#endif