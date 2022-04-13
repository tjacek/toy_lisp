#include "eval.h"
#include "builtin.h"

void interpret(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  int line_counter=0;
  EnvirPtr envir(new Envir());
  init_envir(envir);
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);    
//    tokens->print_types(); 
    try{
      ExprPtr expr= parse_expr(tokens);
      VariablePtr var= eval(expr,envir);
      std::cout << expr->to_str() << std::endl;
      std::cout << to_str(var) << std::endl;      
      envir->print_envir();
    }catch(std::string e){
       std::cout << "Line: " << line_counter << std::endl;
       std::cout << e << std::endl;
       return ; 
    }
    lines.push_back(tokens);
  }
}

VariablePtr eval(ExpPtr expr,EnvirPtr envir){
  if(expr->is_atom()){
    AtomPtr atom=expr->get_atom();
    if(std::holds_alternative<std::string>(*atom)){
      std::string var_name=std::get<std::string>(*atom);
      return envir->get(var_name);
    }
    return atom_to_var(atom);
  }
  ComplexExprPtr complex_expr=expr->get_complex_expr();
  if(complex_expr->check_type("define")){
    return eval_define(complex_expr,envir);
  }
  if(complex_expr->check_type("lambda")){
    return eval_lambda(complex_expr,envir);
  }
  if(complex_expr->check_type("if")){
    return eval_cond(complex_expr,envir);
  }
  return call_eval(complex_expr,envir);
}

VariablePtr eval_define(ComplexExprPtr expr,EnvirPtr envir){
  AtomPtr atom=expr->subexprs[1]->get_atom();
  std::string var_name =std::get<std::string>(*atom);
  VariablePtr var=eval(expr->subexprs[2],envir);
  envir->set(var_name, var);
  return var;
}

VariablePtr eval_lambda(ComplexExprPtr expr,EnvirPtr envir){
  ExprPtr body=expr->subexprs[2];
  ComplexExprPtr args_expr=expr->subexprs[1]->get_complex_expr();
  std::vector<std::string> args;
  for(auto it=args_expr->subexprs.begin(); it != args_expr->subexprs.end(); ++it) {
    std::string name_i= (*it)->to_str();
    args.push_back(name_i);
  }
  FunctionPtr lambda=FunctionPtr(new Lambda(args,body,envir));
  return VariablePtr(new Variable(lambda));
}

VariablePtr eval_cond(ComplexExprPtr expr,EnvirPtr envir){
  VariablePtr cond=eval(expr->subexprs[1],envir);
  if(std::get<float>(*cond)==0){
    return eval(expr->subexprs[3],envir);
  }
  return eval(expr->subexprs[2],envir);
}

VariablePtr call_eval(ComplexExprPtr expr,EnvirPtr envir){
  VariablePtr fun_var=eval(expr->subexprs[0],envir);
  FunctionPtr fun=std::get<FunctionPtr>(*fun_var);
  std::vector<VariablePtr> args;
  for (auto it = expr->subexprs.begin()+1; it != expr->subexprs.end(); ++it) {
    VariablePtr var_i= eval( (*it),envir);
    args.push_back(var_i);
  }
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
  if(this->outer!= nullptr){
    return this->outer->get(name);
  }
  return nullptr;
}

void Envir::set(const std::string &name,VariablePtr value){
  this->current[name]=value;
}

void Envir::set(const std::string & name,FunctionPtr value){
  this->current[name]= VariablePtr(new Variable(value));
}

void Envir::print_envir(){
  for(const auto& [key, value] : this->current) {
    std::cout << '[' << key << "] = " << to_str(value) << ";";
  }
  std::cout << std::endl;  
}

Lambda::Lambda(std::vector<std::string> args,ExprPtr body,EnvirPtr envir){
  this->args=args;
  this->body=body;
  this->envir=envir;
}

VariablePtr Lambda::operator()(std::vector<VariablePtr> & args,EnvirPtr envir){
  EnvirPtr fun_envir=EnvirPtr(new Envir(this->envir));
  for(int i=0;i<args.size();i++){//auto it = args.begin(); it != args.end(); ++it) {
    VariablePtr var_i= args[i];//eval( (*it),envir);
    std::string name_i = this->args[i];
    fun_envir->set(name_i,var_i);
  }
  return eval(this->body,fun_envir);
}

std::string Lambda::to_str(){
  std::string str= "Lambda";
  for (auto it = this->args.begin(); it != this->args.end(); ++it) {
     str+=" "+ (*it);
  }
  return str;
}

int main(){
  interpret("test.lisp");
}