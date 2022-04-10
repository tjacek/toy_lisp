#include "builtin.h"

VariablePtr ArithmeticFunction::call(std::vector<VariablePtr> & args,Envir & envir){
  float first=std::get<float>(*args[0]);
  float second=std::get<float>(*args[1]);
  float result=this->raw_fun(first,second);
  return VariablePtr(new Variable(result));
}

float ArithmeticFunction::raw_fun(float x,float y){
  return x+y;
}

void init_envir(Envir & envir){
  FunctionPtr fun =FunctionPtr(new ArithmeticFunction());
  envir["+"]=VariablePtr(new Variable(fun));
}
