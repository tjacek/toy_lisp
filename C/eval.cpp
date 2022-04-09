#include "eval.h"

void interpret(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  int line_counter=0;
  Envir envir;
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);    
//    tokens->print_types(); 
    try{
      ExprPtr expr= parse_expr(tokens);
      VariablePtr var= eval(expr,envir);
      std::cout << expr->to_str() << std::endl;
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
    return atom;
  }
  ComplexExprPtr complex_expr=expr->get_complex_expr();
  complex_expr->check_type("define");
  return VariablePtr(new Variable(0.0));
}

int main(){
  interpret("test.lisp");
}