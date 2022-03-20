#include "math.h"

Token::Token(std::string str){
  this->type=VAR;
  this->data=str;
}

Token::Token(float x){
  this->type=NUMBER;
  this->data=x;
}

Token::Token(TokenType type){
  this->type=type;
  this->data=0.0;
}

std::string Token::to_str(){
  if(this->type==VAR){
    return std::get<std::string>(this->data);
  }
  if(this->type==NUMBER){
    float value= std::get<float>(this->data);
    return std::to_string(value);
  }
  return std::string(type_to_str(this->type));
}

bool TokenSeq::next_token_is(std::vector<TokenType> & types){
  TokenPtr token=this->peek();
  for(auto it = types.begin(); it != types.end(); ++it) {
    TokenType type_i=(*it);
    if(token->type==type_i){
      return true;
    }
  }
  return false;
}

TokenPtr TokenSeq::except_token(TokenType type){
  std::vector<TokenType> types={type};
  return this->except_token(types);
}

TokenPtr TokenSeq::except_token(std::vector<TokenType> & types){
  TokenPtr token=this->peek();
  if(!this->next_token_is(types)){
    throw "Parser error";
  }
  this->shift();
  return token;
}

constexpr const char* type_to_str(TokenType type_i){
    switch (type_i)
    {
        case TokenType::NUMBER: return "Number";
        case TokenType::VAR: return "Variable";
        case TokenType::EQUAL: return "=";
        case TokenType::PLUS: return "+";
        case TokenType::MINUS: return "-";
        case TokenType::DIVIDE: return "/";
        case TokenType::MULT: return "*";
        case TokenType::READ: return "read";        
        case TokenType::SET: return "set";
        case TokenType::PRINT: return "print";
        default: return "unknown";
    }
}

TokenPtr TokenSeq::peek(){
  return this->tokens[this->current];
}


void TokenSeq::add(TokenPtr token){
  this->tokens.push_back(token);
}

void TokenSeq::shift(){
  this->current++;
}

void TokenSeq::print(){
  this->print(0);
}

void TokenSeq::print_current(){
  this->print(this->current);
}

void TokenSeq::print(int i){
  for (auto it = this->tokens.begin()+i; it != this->tokens.end(); ++it) {
    TokenPtr token_j=(*it);
    std::cout << token_j->to_str() << " ";
  }
}

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  Envir envir;
  while (std::getline(infile, line)){
    TokenSeqPtr tokens= tokenize(line);
    StatementPtr stat_i= parse_statement(tokens);
    eval_statment(stat_i,envir);
    print_envir(envir);
    lines.push_back(tokens);
  }
//  print_lines(lines);
}

TokenSeqPtr tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;
  TokenSeqPtr tokens=TokenSeqPtr(new TokenSeq());
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    TokenPtr token_i;
    if(std::regex_match (str_i,command_reg)){
      token_i=get_inst(str_i);
    } else if(std::regex_match (str_i,number_reg)){
      float value=atof(str_i.c_str());
      token_i= TokenPtr(new Token(value));
    } else if(std::regex_match (str_i,var_reg)){
      token_i= TokenPtr(new Token(str_i));
    } 
    tokens->add(token_i);
  }
  return tokens;
}

TokenPtr get_inst(std::string str_i){
  Token * token_i;
  if(str_i.compare("read")==0){
    token_i= new Token(READ);
  } else if(str_i.compare("set")==0){
    token_i= new Token(SET);
  } else if(str_i.compare("print")==0){
    token_i= new Token(PRINT);
  } else if(str_i.compare("=")==0){
      token_i= new Token(EQUAL);
  } else if(str_i.compare("+")==0){
      token_i= new Token(PLUS);
  } else if(str_i.compare("-")==0){
      token_i= new Token(MINUS);
  } else if(str_i.compare("*")==0){
      token_i=new Token(MULT);
  } else if(str_i.compare("/")==0){
      token_i=new Token(DIVIDE);
  }
  return TokenPtr(token_i);
}

void print_lines(std::vector<TokenSeqPtr> & lines){
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    (*it)->print_current();
    std::cout << std::endl;
  }
}

Statement::Statement(TokenType type,std::string var){
  this->type=type;
  this->var=var;
}

Statement::Statement(TokenType type,std::string var,ExprPtr expr){
  this->type=type;
  this->var=var;
  this->expr=expr;
}

std::string Statement::to_str(){
  return type_to_str(this->type);
}

StatementPtr parse_statement(const TokenSeqPtr & tokens){
  Statement * statement=NULL;
  std::vector<TokenType> types = {READ,SET,PRINT};
  TokenPtr token_i=tokens->except_token(types);
  if(token_i->type==SET){
    std::string var_i= tokens->except_token(VAR)->to_str();
    tokens->except_token(EQUAL);
    ExprPtr expr(NULL);
//    tokens->print_current();
    statement=new Statement(token_i->type,var_i,expr);
  }else{
      std::string var_i=tokens->peek()->to_str();
      statement=new Statement(token_i->type,var_i);
  }
  return StatementPtr(statement);
}

ExprPtr parse_expr(){
  Expr * expr=NULL;
  return ExprPtr(expr);
}

bool is_statement(TokenType type){
  return ( (type==SET || type==READ) || type==PRINT);
}

void print_envir(Envir & envir){
  for(const auto& [key, value] : envir) {
    std::cout << '[' << key << "] = " << value << ";";
  }
  std::cout << std::endl;
}

void eval_statment(StatementPtr statement, Envir & envir){
  if(statement->type==READ){
    int value;
    std::cin >> value;
    envir[statement->var]=value;
  }
  if(statement->type==SET){
    envir[statement->var]=0.0;
  }
  if(statement->type==PRINT){
    std::cout << envir[statement->var] << std::endl;
  }
}

int main(){
  parse("test.math");
}