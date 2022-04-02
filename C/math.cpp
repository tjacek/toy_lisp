#include "math.h"

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  Envir envir;
  int line_counter=0;
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);
    tokens->print_types();
    try{
      StatementPtr stat_i= parse_statement(tokens);
      eval_statment(stat_i,envir);
    }catch(std::string e){
       std::cout << "Line: " << line_counter << std::endl;
       std::cout << e << std::endl;
       return ; 
    }
    print_envir(envir);
    lines.push_back(tokens);
  }
//  print_lines(lines);
}

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

void TokenSeq::print_types(){
  for(auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
    std::cout << type_to_str( (*it)->type) <<" ";
  }
  std::cout << std::endl;
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

bool TokenSeq::except_token(TokenType type){
  std::vector<TokenType> types={type};
  return this->except_token(types);
}

bool TokenSeq::except_token(std::vector<TokenType> & types){
  TokenPtr token=this->peek();
//  this->print_current();
  if(this->current== this->tokens.size()-1){
    return false;
  }
  if(!this->next_token_is(types)){
    std::string exc="Parser error " + std::to_string(this->current) + " "; 
    exc+="Excepted {";
    for(auto it = types.begin(); it != types.end(); ++it) {
      exc+=" ";
      exc+=type_to_str(*it);
    }
    exc+= "} got "; 
    exc+= type_to_str(token->type);
    throw exc;
  }
  this->shift();
  return true;
}

TokenPtr TokenSeq::peek(){
  return this->tokens[this->current];
}

void TokenSeq::add(TokenPtr token){
  this->tokens.push_back(token);
}

void TokenSeq::shift(){
  if(this->current < this->tokens.size()-1){
    this->current++;
  }
}

void TokenSeq::print(){
  this->print(0);
}

void TokenSeq::print_current(){
//  std::cout << this->current;
  this->print(this->current);
}

void TokenSeq::print(int i){
  for (auto it = this->tokens.begin()+i; it != this->tokens.end(); ++it) {
    TokenPtr token_j=(*it);
    std::cout << token_j->to_str() << " ";
  }
  std::cout << std::endl;
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

Expr::Expr(TokenType type,ExprPtr left,ExprPtr right){
  this->is_leaf=false;
  this->type=type;
  this->data=std::make_pair(left,right);
}

Expr::Expr(TokenPtr token){
  this->is_leaf=true;
  this->type=token->type;
  this->data=token;
}

std::string Expr::to_str(){
  if(this->is_leaf){
    return type_to_str(this->type);
  }else{
    std::string rep="";
    ptr_pair<Expr> pair = std::get<ptr_pair<Expr>>(this->data);
    if(pair.first!=NULL){
      rep+=" "+pair.first->to_str() +std::string( "\n");
    }
    rep+=type_to_str(this->type)+std::string("\n");
    if(pair.second!=NULL){
      rep+=" "+pair.second->to_str()+std::string("\n");
    }

    return rep;
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
//  std::cout << "parse_statement" << std::endl;
//  tokens->print_current();
  Statement * statement=NULL;
  std::vector<TokenType> types = {READ,SET,PRINT};
  TokenPtr token_i=tokens->peek();

  tokens->except_token(types);
  if(token_i->type==SET){
    std::string var_i=tokens->peek()->to_str();
    tokens->except_token(VAR);
    tokens->except_token(EQUAL);
    ExprPtr expr=parse_expr(tokens);
    statement=new Statement(token_i->type,var_i,expr);
//    std::cout << "*******************" << std::endl;
//    std::cout << expr->to_str();
//    std::cout << "*******************" << std::endl;
  }else{
      std::string var_i=tokens->peek()->to_str();
      statement=new Statement(token_i->type,var_i);
  }
  return StatementPtr(statement);
}

ExprPtr parse_expr(const TokenSeqPtr & tokens){
//  std::cout << "parse_expr" << std::endl;
//  tokens->print_current();
  ExprPtr expr=parse_product(tokens);
  std::vector<TokenType> types = {PLUS,MINUS};
  while( tokens->except_token(types)){
    TokenType type_i=tokens->peek()->type;
    tokens->shift();
    expr=ExprPtr(new Expr(type_i,expr,parse_product(tokens)));
  }
//  tokens->print_current();
  return expr;
}

ExprPtr parse_product(const TokenSeqPtr & tokens){
//  std::cout << "parse_product" << std::endl;
//  tokens->print_current();

  ExprPtr expr=parse_factor(tokens);
  std::vector<TokenType> types = {DIVIDE,MULT};
  TokenType type_i=tokens->peek()->type;
  while( tokens->except_token(types)){
    expr=ExprPtr(new Expr(type_i,expr,parse_factor(tokens)));
    type_i=tokens->peek()->type;
  }
  return expr;
}

ExprPtr parse_factor(const TokenSeqPtr & tokens){
//  std::cout << "parse_factor" << std::endl;
//  tokens->print_current();

  Expr * expr=NULL;
  std::vector<TokenType> types = {NUMBER,VAR,BRACKET};

  TokenPtr token_i = tokens->peek();
  tokens->except_token(types);
  if(token_i->type==VAR || token_i->type==NUMBER){
    expr=new Expr(token_i);
  }
  return ExprPtr(expr);
}

void print_envir(Envir & envir){
  for(const auto& [key, value] : envir) {
    std::cout << '[' << key << "] = " << value << ";";
  }
  std::cout << std::endl;
}

void eval_statment(const StatementPtr & statement, Envir & envir){
  if(statement->type==READ){
    int value;
    std::cin >> value;
    envir[statement->var]=value;
  }
  if(statement->type==SET){
    ExprPtr expr= *statement->expr;
    envir[statement->var]=eval_expr(expr,envir);
  }
  if(statement->type==PRINT){
    std::cout << "$" << envir[statement->var] << std::endl;
  }
}

float eval_expr(const ExprPtr & expr, Envir & envir){
  if(expr->is_leaf){
    TokenPtr token=std::get<TokenPtr>(expr->data);
    if(token->type==NUMBER){
      return std::get<float>(token->data);
    }
    if(token->type==VAR){
      std::string var=std::get<std::string>(token->data);
      return envir[var];
    }
  }else{
    ptr_pair<Expr> pair=std::get<ptr_pair<Expr>>(expr->data);
    float lvalue= eval_expr(pair.first,envir);
    float rvalue= eval_expr(pair.second,envir);
    if(expr->type==MULT){
      return lvalue*rvalue;
    }
    if(expr->type==PLUS){
      return lvalue+rvalue;
    }
    if(expr->type==MINUS){
      return lvalue-rvalue;
    }
    if(expr->type==DIVIDE){
      return lvalue/rvalue;
    }
  }
  return 0;
}

int main(){
  parse("test.math");
}