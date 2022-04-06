#include "tokens.h"

TokenSeqPtr tokenize(std::string line){
  replace_string(line,"(","  ( ");
  replace_string(line,")"," ) ");

  TokenSeqPtr tokens=TokenSeqPtr(new TokenSeq());
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;

  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    TokenType type_i;
    if(std::regex_match (str_i,command_reg)){
      type_i= SYNTAX;
    } else if(std::regex_match (str_i,number_reg)){
      type_i= NUMBER;
    } else if(std::regex_match (str_i,var_reg)){
      type_i= VAR;
    }
    TokenPtr token_i= TokenPtr(new Token(type_i,str_i));
    tokens->add(token_i);
  }
  return tokens;
}

void replace_string(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

Token::Token(TokenType type,std::string str){
  this->type=type;
  this->data=str;
}

std::string Token::get_type(){
  switch(this->type){
      case TokenType::NUMBER: return "Number";
      case TokenType::VAR: return "Variable";
      default: return this->data;
  }
}

TokenPtr TokenSeq::peek(){
  return this->tokens[this->current];;
}

void TokenSeq::shift(){
  if(this->current < this->tokens.size()-1){
    this->current++;
  }
}

void TokenSeq::add(TokenPtr token){
  this->tokens.push_back(token);
}

void TokenSeq::print(int i){
  for (auto it = this->tokens.begin()+i; it != this->tokens.end(); ++it) {
    TokenPtr token_j=(*it);
    std::cout << token_j->data << " ";
  }
  std::cout << std::endl;
}

void TokenSeq::print_types(){
  for(auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
    std::cout <<  (*it)->get_type() <<" ";
  }
  std::cout << std::endl;
}