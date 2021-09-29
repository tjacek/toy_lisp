#include "builtin.h"

Object * ArithmeticOperation::call(std::list<Object*> args,Envir envir){
  float value=0; 
  Object * left= (*args.begin());
  Object * right= (*args.end());
  if(left->type==ObjectType::number_type &&
    right->type==ObjectType::number_type ){
    NumberObject * l= (NumberObject*)left;
    NumberObject * r= (NumberObject*)right; 
    value=this->fun(l->value,r->value);  
  }
  Object * result=new NumberObject(value);
  return result;
}

Object * Define::call(std::list<Object*> args,Envir envir){
  Object * left= (*args.begin());
  Object * right= (*args.end());
  if(left->type==ObjectType::string_type){
    StringObject * name=(StringObject*) left;
    envir[name->value]=right;
  }
    return right;
  }

Object * ArithmeticOperation::eval(Envir envir){
  return this;
}


Object * Define::eval(Envir envir){
  return this;
}


Object * Add::eval(Envir envir){
  return this;
}

Object * Mult::eval(Envir envir){
  return this;
}


std::string Define::to_str(){
    return "define";
} 

float Add::fun(float x,float y){
  return x+y;
}

std::string Add::to_str(){
  return "+";
} 
 
float Mult::fun(float x,float y){
  return x*y;
}

std::string Mult::to_str(){
    return "*";
}

   

