#include "eval.h"

typedef float (*Raw_fun)(float, float) ;

class ArithmeticFunction:public Function{
  public:
    VariablePtr operator()(std::vector<VariablePtr> & args,EnvirPtr envir);
    virtual float call(float,float)=0;
};

void init_envir(EnvirPtr envir);