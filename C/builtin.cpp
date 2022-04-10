#include "builtin.h"

VariablePtr ArithmeticFunction::call(std::vector<VariablePtr> & args,Envir & envir){
  float first=std::get<float>(*args[0]);
  float second=std::get<float>(*args[1]);
  float result=this->raw_fun(first,second);
  return VariablePtr(new Variable(result));
}


class Add:public ArithmeticFunction{
  float raw_fun(float x,float y) { return x+y;};
};

class Mult:public ArithmeticFunction{
  float raw_fun(float x,float y) { return x*y;};
};

class Sub:public ArithmeticFunction{
  float raw_fun(float x,float y) { return x-y;};
};

class Div:public ArithmeticFunction{
  float raw_fun(float x,float y) { return x/y;};
};

void init_envir(Envir & envir){
  FunctionPtr fun_add =FunctionPtr(new Add());
  envir["+"]=VariablePtr(new Variable(fun_add));
  FunctionPtr fun_mult =FunctionPtr(new Mult());
  envir["*"]=VariablePtr(new Variable(fun_mult));
  FunctionPtr fun_sub =FunctionPtr(new Sub());
  envir["-"]=VariablePtr(new Variable(fun_sub));
  FunctionPtr fun_div =FunctionPtr(new Div());
  envir["/"]=VariablePtr(new Variable(fun_div));
}