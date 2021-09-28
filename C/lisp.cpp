#include "lisp.h"
#include "builtin.h"

int main(){
	std::string program = "(begin (define r 10) (* pi (* r r)))";
//    auto tokens=tokenize(program);
//    Expr * exp=read_from_tokens(tokens);
//    exp->show();

  std::map<std::string,Object*>  envir;
  envir["pi"]= new NumberObject(3.141);
  envir["define"]=new Define();
  envir["+"]=new Add();
  envir["*"]=new Mult();
}