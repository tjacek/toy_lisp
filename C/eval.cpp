#include "eval.h"
#include "builtin.h"

void interpret(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  int line_counter=0;
  Envir envir;
  init_envir(envir);
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);    
//    tokens->print_types(); 
    try{
      ExprPtr expr= parse_expr(tokens);
      VariablePtr var= eval(expr,envir);
      std::cout << expr->to_str() << std::endl;
      envir.print_envir();
    }catch(std::string e){
       std::cout << "Line: " << line_counter << std::endl;
       std::cout << e << std::endl;
       return ; 
    }
    lines.push_back(tokens);
  }
}

VariablePtr eval(ExpPtr expr,Envir & envir){
  if(expr->is_atom()){
    AtomPtr atom=expr->get_atom();
    if(std::holds_alternative<std::string>(*atom)){
      std::string var_name=std::get<std::string>(*atom);
      return envir.get(var_name);
    }
    return atom_to_var(atom);
  }
  ComplexExprPtr complex_expr=expr->get_complex_expr();
  if(complex_expr->check_type("define")){
    return eval_define(complex_expr,envir);
  }
  return call_eval(complex_expr,envir);
}

VariablePtr eval_define(ComplexExprPtr expr,Envir & envir){
  AtomPtr atom=expr->subexprs[1]->get_atom();
  std::string var_name =std::get<std::string>(*atom);
  VariablePtr var=eval(expr->subexprs[2],envir);
  envir.set(var_name, var);
  return var;
}

VariablePtr call_eval(ComplexExprPtr expr,Envir & envir){
  VariablePtr fun_var=eval(expr->subexprs[0],envir);
  FunctionPtr fun=std::get<FunctionPtr>(*fun_var);
  std::vector<VariablePtr> args;
  for (auto it = expr->subexprs.begin()+1; it != expr->subexprs.end(); ++it) {
    VariablePtr var_i= eval( (*it),envir);
    args.push_back(var_i);
  }
  std::cout << args.size() << std::endl;
  return (*fun)(args,envir);
}

VariablePtr atom_to_var(AtomPtr atom){
  if(std::holds_alternative<std::string>(*atom)){
    std::string str= std::get<std::string>(*atom);
    return VariablePtr(new Variable(str));
  }
  float value=std::get<float>(*atom);
  return VariablePtr(new Variable(value));
}

std::string to_str(VariablePtr variable){
  if(std::holds_alternative<std::string>(*variable)){
    return std::get<std::string>(*variable);
  }else if(std::holds_alternative<float>(*variable)){
     return std::to_string(std::get<float>(*variable));
  }
  return std::get<FunctionPtr>(*variable)->to_str();
}

Envir::Envir(std::shared_ptr<Envir> outer){
  this->outer=outer;
}

VariablePtr  Envir::get(const std::string & name){
  if(this->current.contains(name) ){
    return this->current[name];
  }
  return this->current[name];
}

void Envir::set(const std::string &name,VariablePtr value){
  this->current[name]=value;
}

void Envir::print_envir(){
  for(const auto& [key, value] : this->current) {
    std::cout << '[' << key << "] = " << to_str(value) << ";";
  }
  std::cout << std::endl;  
}


int main(){
  interpret("test.lisp");
}