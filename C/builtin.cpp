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

void init_envir(EnvirPtr envir){
  FunctionPtr fun_add =FunctionPtr(new Add());
  envir->set("+",VariablePtr(new Variable(fun_add)));
  FunctionPtr fun_mult =FunctionPtr(new Mult());
  envir->set("*",VariablePtr(new Variable(fun_mult)));
  FunctionPtr fun_sub =FunctionPtr(new Sub());
  envir->set("-",VariablePtr(new Variable(fun_sub)));
  FunctionPtr fun_div =FunctionPtr(new Div());
  envir->set("/",VariablePtr(new Variable(fun_div)));
}