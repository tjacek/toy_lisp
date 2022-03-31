#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <variant>
#include <memory>
#include <optional>
#ifndef MATH
#define MATH

enum TokenType {NUMBER,VAR,EQUAL,SET,PRINT,READ,
    PLUS,MINUS,DIVIDE,MULT,BRACKET};

const static std::regex ws_reg("\\s+");
const static std::regex number_reg("-?\\d+(\\.\\d+)?");
const static std::regex command_reg("[\\+\\-\\*\\/=()]|set|read|print");
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

typedef std::shared_ptr<Token> TokenPtr;
constexpr const char* type_to_str(TokenType type_i);

class TokenSeq{
  private:
    std::vector<TokenPtr> tokens;
    int current=0;

  public:
    bool next_token_is(std::vector<TokenType> & types);
//    TokenPtr except_token(std::vector<TokenType> & types);
//    TokenPtr except_token(TokenType type);
    bool except_token(std::vector<TokenType> & types);
    bool except_token(TokenType type);    
    TokenPtr peek();
    void add(TokenPtr token);
    void shift();

    void print();
    void print(int i);
    void print_current();
    void print_types();
};

typedef std::shared_ptr<TokenSeq> TokenSeqPtr;
TokenSeqPtr tokenize(std::string line);
void print_lines(std::vector<TokenSeqPtr> & lines);
TokenPtr get_inst(std::string str_i);

template<class T>
using ptr_pair = std::pair<std::shared_ptr<T>,std::shared_ptr<T>>;

class Expr{
  public:
    bool is_leaf;
    TokenType type;
    std::variant<TokenPtr,ptr_pair<Expr>> data;
    Expr(TokenType type,std::shared_ptr<Expr> left,std::shared_ptr<Expr> right);
    Expr(TokenPtr token);
    std::string to_str();
};

typedef std::shared_ptr<Expr> ExprPtr;

class Statement{
  public:
    TokenType type;
    std::string var;
    std::optional<ExprPtr> expr;
    Statement(TokenType type,std::string var);
    Statement(TokenType type,std::string var,ExprPtr expr);
    std::string to_str();
};

typedef std::shared_ptr<Statement> StatementPtr;
StatementPtr parse_statement(const TokenSeqPtr & tokens);
ExprPtr parse_expr(const TokenSeqPtr & tokens);
ExprPtr parse_product(const TokenSeqPtr & tokens);
ExprPtr parse_factor(const TokenSeqPtr & tokens);

typedef std::map<std::string,float> Envir;

void print_envir(Envir & envir);
void eval_statment(StatementPtr statement, Envir & envir);

#endif