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
    tokens->print_types(); 
    try{
      parse_expr(tokens);
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
    std::cout << token->data;
    throw std::string("unexpected )");
  }
  ExprPtr expr= ExprPtr(new Expr<ComplexExpr>());
  if(token->is_start()){
    ComplexExprPtr complex_expr(  new ComplexExpr());
    while(!token->is_end()){
      complex_expr->subexprs.push_back(parse_expr(tokens));
      tokens->shift();
    }
    expr->data=complex_expr;
    return expr;//expr;
  }
  tokens->shift();
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

int main(){
  interpret("test.lisp");
}