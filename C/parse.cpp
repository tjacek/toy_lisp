#include "tokens.h"
#include "parse.h"

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
bool Expr<T>::is_atom(){
  return std::holds_alternative<AtomPtr>(this->data);
}

template<class T>
AtomPtr Expr<T>::get_atom(){
  return std::get<AtomPtr>(this->data);
}

template<class T>
std::shared_ptr<T> Expr<T>::get_complex_expr(){
  return std::get<ComplexExprPtr>(this->data);
}

template<class T>
std::string Expr<T>::to_str(){
  if(this->is_atom()){
    AtomPtr atom =this->get_atom();
    if(std::holds_alternative<float>(*atom)){
      float value=std::get<float>(*atom);
      return std::to_string(value);
    }else{
      return std::get<std::string>(*atom);
    }
  }
  ComplexExprPtr complex_expr=this->get_complex_expr(); 
  return complex_expr->to_str();
}

bool ComplexExpr::check_type(std::string type){
  ExprPtr expr=this->subexprs[0];
  if(not expr->is_atom()){
    return false;
  }
  AtomPtr atom=expr->get_atom();
  if(std::holds_alternative<std::string>(*atom)){
    return std::get<std::string>(*atom).compare(type);
  }
  return false;
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