#include "tokens.h"
#include "parse.h"

void interpret(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  int line_counter=0;
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);    
//    tokens->print_types(); 
    try{
      ExprPtr expr= parse_expr(tokens);
      std::cout << expr->to_str() << std::endl;
    }catch(std::string e){
       std::cout << "Line: " << line_counter << std::endl;
       std::cout << e << std::endl;
       return ; 
    }
    lines.push_back(tokens);
  }
}

ExprPtr parse_expr(const TokenSeqPtr & tokens){
  TokenPtr token=tokens->peek();
  if(token->is_end()){
    throw std::string("unexpected )");
  }
  tokens->shift();
  ExprPtr expr= ExprPtr(new Expr<ComplexExpr>());
  if(token->is_start()){
    ComplexExprPtr complex_expr(  new ComplexExpr());
    while(!token->is_end()){
      complex_expr->subexprs.push_back(parse_expr(tokens));
      token=tokens->peek();
    }
    tokens->shift();
    expr->data=complex_expr;
    return expr;
  }
  expr->data=parse_atom(token);
  return expr;
}

AtomPtr parse_atom(const TokenPtr & token){
  if(token->type==NUMBER){
    float value=std::atof(token->data.c_str());
    return AtomPtr(new Atom(value));
  }else{
     return AtomPtr(new Atom(token->data));
  }
}

template<class T>
std::string Expr<T>::to_str(){
  if(std::holds_alternative<AtomPtr>(this->data)) {
    AtomPtr atom = std::get<AtomPtr>(this->data);
    if(std::holds_alternative<float>(*atom)){

      float value=std::get<float>(*atom);
      return std::to_string(value);
    }else{
      return std::get<std::string>(*atom);
    }
  }
  ComplexExprPtr complex_expr= std::get<ComplexExprPtr>(this->data);
  return complex_expr->to_str();
}

std::string ComplexExpr::to_str(){
  std::string expr_string="[";
  for (auto it = this->subexprs.begin(); it != this->subexprs.end(); ++it) {
    expr_string+= (*it)->to_str();
    expr_string+=" ";
  }
  expr_string+="]";
  return expr_string;
}

int main(){
  interpret("test.lisp");
}