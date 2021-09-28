#include "lisp.h"

class ArithmeticOperation:public Object{
   public:
      ObjectType type=ObjectType::operator_type;
      virtual Object * eval(Envir envir);
      virtual float fun(float x,float y)=0;
      Object * call(std::list<Object*> args,Envir envir);
//      virtual std::string to_str();
};

class Define:public Object{
  public:
    ObjectType type=ObjectType::operator_type;
    Object * eval(Envir envir);
    Object * call(std::list<Object*> args,Envir envir);
    std::string to_str();
};
class Add:public ArithmeticOperation{
  public:
    virtual Object * eval(Envir envir);
    float fun(float x,float y);
    std::string to_str();
};

class Mult:public ArithmeticOperation{
  public:
    virtual Object * eval(Envir envir);
    float fun(float x,float y);
    std::string to_str();
};