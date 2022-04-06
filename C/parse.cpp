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

/*    try{
      StatementPtr stat_i= parse_statement(tokens);
      eval_statment(stat_i,envir);
    }catch(std::string e){
       std::cout << "Line: " << line_counter << std::endl;
       std::cout << e << std::endl;
       return ; 
    }*/

    lines.push_back(tokens);
  }
}

ExprPtr parse_expr(const TokenSeqPtr & tokens){
  TokenPtr token=tokens->peek();
  if(token->is_end()){
    throw "unexpected )";
  }
  ExprPtr expr= ExprPtr(new Expr<ComplexExpr>());

  if(token->is_start()){
    ComplexExprPtr complex_expr(new ComplexExpr());
    while(!token->is_end()){
//      expr->subexpr
      tokens->shift();
    }
    expr->data=complex_expr;
    return expr;
  }
  tokens->shift();
  
  return expr;
}

int main(){
  interpret("test.lisp");
}