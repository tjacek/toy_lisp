#include "eval.h"

typedef float (*Raw_fun)(float, float) ;

class ArithmeticFunction:public Function{
  public:
    VariablePtr call(std::vector<VariablePtr> & args,Envir & envir);
    float raw_fun(float,float);
};

void init_envir(Envir & envir);

/*float raw_mult(float x,float y){ return x*y;}

float raw_add(float x,float y){return x+y;}

float raw_div(float x,float y){return x/y;}

float raw_sub(float x,float y) { return x-y;}*/
