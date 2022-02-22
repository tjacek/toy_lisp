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
//    std::cout << line << "\n";
    tokenize(line);
  }
}

std::vector<Token> tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws,-1);
  std::sregex_token_iterator end;
  std:: vector<Token> tokens;
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    std::cout << str_i <<"$";
  }
  std::cout << std::endl;
  return tokens;
}

int main(){
  //Token a(5.0);
  parse("test.math");
}