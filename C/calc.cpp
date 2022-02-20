#include "calc.h"

void Calculator::push(double value){
  this->stack.push_back(value);
}

double Calculator::apply(std::string operation){
  double x =this->stack.back();
  this->stack.pop_back();
  double y =this->stack.back();
  this->stack.pop_back();  
  float value;
  if(operation.compare("+")==0){
      value= x+y;
  }
  if(operation.compare("-")==0){
      value= y-x;
  }
  if(operation.compare("*")==0){
      value= x*y;
  }
  if(operation.compare("\\/")==0){
      value= y/x;
  }
  this->stack.push_back(value);
  return value;
}

double Calculator::peek(){
  return this->stack.back();
}

double reverse_polish(std::string program){
  std::regex ws("\\s+");
  std::sregex_token_iterator iter(program.begin(),
    program.end(),ws,-1);
  std::sregex_token_iterator end;
  
  std::regex digit("\\d+"); 
  std::regex operation("(\\+)|(\\-)|(\\*)|(\\/)");
  std::cmatch m;
  Calculator calc;
  for ( ; iter != end; ++iter){
      std::string str_i=*iter;
      if(std::regex_match (str_i,digit)){
          calc.push( atof(str_i.c_str()));
      }
      if(std::regex_match (str_i,operation)){
          calc.apply(str_i);
      }
      std::cout << calc.peek() << '\n';
  }
  return calc.peek();
}

int main(){
  std::string program = "2 7 + 4 *";
  std::cout << reverse_polish(program) << "\n";
}