#include "lisp.h"
//#include "tokens.cpp"



int main(){
	std::string program = "(begin (define r 10) (* pi (* r r)))";
    auto tokens=tokenize(program);
    Expr * exp=read_from_tokens(tokens);
    exp->show();
}