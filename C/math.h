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
    PLUS,MINUS,DIVIDE,MULT};

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
    TokenPtr except_token(std::vector<TokenType> & types);
    TokenPtr except_token(TokenType type);

    TokenPtr peek();
    void add(TokenPtr token);
    void print();
    void print(int i);
    void print_current();
    void shift();
};

typedef std::shared_ptr<TokenSeq> TokenSeqPtr;
TokenSeqPtr tokenize(std::string line);
void print_lines(std::vector<TokenSeqPtr> & lines);
TokenPtr get_inst(std::string str_i);

class Expr{
  public:
    bool is_leaf;
    TokenType type;
    std::variant<TokenPtr,std::pair<Expr*,Expr*>> data;
    Expr(TokenType type,Expr* left,Expr* right);
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

bool is_statement(TokenType type);

typedef std::map<std::string,float> Envir;

void print_envir(Envir & envir);
void eval_statment(StatementPtr statement, Envir & envir);

#endif