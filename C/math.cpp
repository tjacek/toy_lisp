#include "math.h"
  
Token::Token(double value){
  this->type=NUMBER;
  this->value=value;
}

Token::Token(TokenType type){
	this->type=type;
	this->value=0.0;
}

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  while (std::getline(infile, line)){
    tokenize(line);
  }
}

std::vector<Token> tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;
  std:: vector<Token> tokens;
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    if(std::regex_match (str_i,number_reg)){
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,var_reg)){
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,command_reg)){
      std::cout << str_i << std::endl;
    }
  }
  std::cout << std::endl;
  return tokens;
}

int main(){
  //Token a(5.0);
  parse("test.math");
}