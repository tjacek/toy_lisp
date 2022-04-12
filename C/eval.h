#include "tokens.h"
#include "parse.h"
#ifndef EVAL
#define EVAL

class Function;

typedef std::variant<float,std::string,std::shared_ptr<Function>> Variable;
typedef std::shared_ptr<Variable> VariablePtr;
VariablePtr atom_to_var(AtomPtr atom);

class Envir{
  public:
    std::map<std::string,VariablePtr> current;
    std::shared_ptr<Envir> outer;

    VariablePtr get(const std::string &var);
    void set(const std::string & name,VariablePtr value);
    void print_envir();
    Envir(std::shared_ptr<Envir> outer=nullptr);
};

class Function{
  public:
  	virtual VariablePtr operator()(std::vector<VariablePtr> & args,Envir & envir)=0;
  	virtual std::string to_str()=0;
};
typedef std::shared_ptr<Function> FunctionPtr;

//typedef std::map<std::string,VariablePtr> Envir;

VariablePtr eval(ExpPtr expr,Envir & envir);
VariablePtr eval_define(ComplexExprPtr expr,Envir & envir);
VariablePtr call_eval(ComplexExprPtr expr,Envir & envir);
std::string to_str(VariablePtr variable);
#endif