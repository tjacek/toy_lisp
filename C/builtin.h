#include "eval.h"

typedef float (*Raw_fun)(float, float) ;

class ArithmeticFunction:public Function{
  public:
    VariablePtr call(std::vector<VariablePtr> & args,Envir & envir);
    virtual float raw_fun(float,float)=0;
};

void init_envir(Envir & envir);