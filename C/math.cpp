#include "math.h"

NumberToken::NumberToken(double value){
  this->type=NUMBER;
  this->value=value;
}

std::string NumberToken::to_str(){
  return std::to_string(this->value);
}

StringToken::StringToken(TokenType type,std::string value){
  this->type=type;
  this->value=value;
}

std::string StringToken::to_str(){
  return this->value;
}

void parse(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  while (std::getline(infile, line)){
    std::vector<Token*> tokens= tokenize(line);
    std::cout << tokens.size() << std::endl;
  }
}

std::vector<Token*> tokenize(std::string line){
  std::sregex_token_iterator iter(line.begin(),line.end(),ws_reg,-1);
  std::sregex_token_iterator end;
  std:: vector<Token*> tokens;
  for ( ; iter != end; ++iter){
    std::string str_i=*iter;
    Token* token_i;
    if(std::regex_match (str_i,number_reg)){
      double value=atof(str_i.c_str());
      token_i= new NumberToken(value);
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,var_reg)){
      token_i=new StringToken(VAR,str_i);
      std::cout << str_i << std::endl;
    } else if(std::regex_match (str_i,command_reg)){
      token_i = new StringToken(COMMAND,str_i);
      std::cout << str_i << std::endl;
    }
    tokens.push_back(token_i);
  }
  return tokens;
}

int main(){
  //Token a(5.0);
  parse("test.math");
}