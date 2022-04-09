#include "tokens.h"
#include "parse.h"
#ifndef EVAL
#define EVAL

typedef std::variant<float,std::string> Variable;
typedef std::shared_ptr<Variable> VariablePtr;

typedef std::map<std::string,VariablePtr> Envir;
VariablePtr eval(ExpPtr expr,Envir & envir);

#endif