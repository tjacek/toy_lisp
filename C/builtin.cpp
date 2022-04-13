#include "builtin.h"

VariablePtr ArithmeticFunction::operator()(std::vector<VariablePtr> & args,EnvirPtr envir){
  float first=std::get<float>(*args[0]);
  float second=std::get<float>(*args[1]);
  float result=this->call(first,second);
  return VariablePtr(new Variable(result));
}

class Add:public ArithmeticFunction{
  float call(float x,float y) { return x+y;};
  std::string to_str(){ return "+";};
};

class Mult:public ArithmeticFunction{
  float call(float x,float y) { return x*y;};
  std::string to_str(){ return "*";};

};

class Sub:public ArithmeticFunction{
  float call(float x,float y) { return x-y;};
    std::string to_str(){ return "-";};
};

class Div:public ArithmeticFunction{
  float call(float x,float y) { return x/y;};
  std::string to_str(){ return "/";};
};

class Eq:public ArithmeticFunction{
  float call(float x,float y) { return (float)(x==y);};
  std::string to_str(){ return "=";};
};

void init_envir(EnvirPtr envir){
  envir->set("+",FunctionPtr(new Add()));
  envir->set("*",FunctionPtr(new Mult()));
  envir->set("-",FunctionPtr(new Sub()));
  envir->set("/",FunctionPtr(new Div()));
  envir->set("=",FunctionPtr(new Eq()));
}