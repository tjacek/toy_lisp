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

typedef std::shared_ptr<Envir> EnvirPtr;

class Function{
  public:
  	virtual VariablePtr operator()(std::vector<VariablePtr> & args,EnvirPtr envir)=0;
  	virtual std::string to_str()=0;
};
typedef std::shared_ptr<Function> FunctionPtr;

/*class Lambda: public Function{
  public:
  	std::vector<std::string> args;
  	ComplexExprPtr body;
    EnvirPtr envir;
};*/

VariablePtr eval(ExpPtr expr,EnvirPtr envir);
VariablePtr eval_define(ComplexExprPtr expr,EnvirPtr envir);
VariablePtr call_eval(ComplexExprPtr expr,EnvirPtr envir);
std::string to_str(VariablePtr variable);
#endif