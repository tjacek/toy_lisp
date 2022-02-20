#include "calc.h"

void Calculator::push(double value){
}

double Calculator::apply(double value){
  return 0;
}

double reversed_polish(std::string program){
  std::regex ws("\\s+");
  std::sregex_token_iterator iter(program.begin(),
    program.end(),ws,-1);
  std::sregex_token_iterator end;
  
  std::regex digit("\\d+"); 
  std::regex operation("(\\+)|(\\-)|(\\*)|(\\/)");
  std::cmatch m;
  for ( ; iter != end; ++iter){
      std::string str_i=*iter;
      if(std::regex_match (str_i,digit)){
          std::cout << "OK";
      }
      if(std::regex_match (str_i,operation)){
          std::cout << "UU";
      }
      std::cout << *iter << '\n';
  }
  return 0;
}

int main(){
  std::string program = "2 7 + 4 *";
  std::cout << reversed_polish(program) << "\n";
}