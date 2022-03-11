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
        default: return "unknown";
    }
}

void TokenSeq::add(Token * token){
  this->tokens.push_back(token);
}

void TokenSeq::print(){
  for (auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
    Token* token_j=(*it);
    std::cout << token_j->to_str() << " ";
  }
}

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  while (std::getline(infile, line)){
    TokenSeqPtr tokens= tokenize(line);
//    parse_statement(tokens);
    lines.push_back(tokens);
  }
  print_lines(lines);
}

TokenSeqPtr tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;
  TokenSeqPtr tokens=TokenSeqPtr(new TokenSeq());
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    Token* token_i;
    if(std::regex_match (str_i,number_reg)){
      float value=atof(str_i.c_str());
      token_i= new Token(value);
    } else if(std::regex_match (str_i,var_reg)){
      token_i=new Token(str_i);
    } else if(std::regex_match (str_i,command_reg)){
      if(str_i.compare("=")==0){
        token_i = new Token(EQUAL);
      } else if(str_i.compare("+")==0){
        token_i=new Token(PLUS);
      } else if(str_i.compare("-")==0){
        token_i=new Token(MINUS);
      } else if(str_i.compare("*")==0){
        token_i=new Token(MULT);
      } else if(str_i.compare("/")==0){
        token_i=new Token(DIVIDE);
      }
    }
    tokens->add(token_i);
  }
  return tokens;
}

void print_lines(std::vector<TokenSeqPtr> & lines){
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    (*it)->print();
    std::cout << std::endl;
  }
}

/*ASTree * parse_statement(Line &line){
  std::cout << is_token(0,"read",line);
  return NULL;
}

bool is_token(int i,std::string symbol,Line & line){
 Token * token_i=line.at(i);
 if(token_i->type==NUMBER){
   return false;
 }
 StringToken * str_token=(StringToken*) token_i;
 return str_token->value.compare(symbol)==0;
}*/

int main(){
  parse("test.math");
}