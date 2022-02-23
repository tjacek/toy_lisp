#include "math.h"

NumberToken::NumberToken(double value){
  this->type=NUMBER;
  this->value=value;
}

StringToken::StringToken(TokenType type,std::string value){
  this->type=type;
  this->value=value;
}

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  while (std::getline(infile, line)){
    std::vector<Token> tokens= tokenize(line);
    std::cout << tokens.size() << std::endl;
  }
}

std::vector<Token> tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;
  std:: vector<Token> tokens;
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    if(std::regex_match (str_i,number_reg)){
      double value=atof(str_i.c_str());
      tokens.push_back(NumberToken(value));
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,var_reg)){
      tokens.push_back(StringToken(VAR,str_i));
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,command_reg)){
      tokens.push_back(StringToken(COMMAND,str_i));
      std::cout << str_i << std::endl;
    }
  }
  return tokens;
}

int main(){
  //Token a(5.0);
  parse("test.math");
}