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
//    std::cout << stat_i->to_str() << std::endl;
    eval_statment(stat_i,envir);
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

std::string Statement::to_str(){
  return type_to_str(this->type);
}

StatementPtr parse_statement(const TokenSeqPtr & tokens){
  Statement * statement=NULL;
  TokenPtr token_i=tokens->peek();
  if(is_statement(token_i->type)){
    TokenType type_i=token_i->type;
      tokens->shift();
      std::string var_i=tokens->peek()->to_str(); 
      statement=new Statement(type_i,var_i); 
  }else{
    std::cout << "ERROR " << (token_i->type) << std::endl;
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