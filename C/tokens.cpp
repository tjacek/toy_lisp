#include "lisp.h"

std::list<std::string> tokenize(std::string program){
    auto l_program=regex_replace(program,regex("\\("),"( ");   
    auto r_program=regex_replace(l_program,regex("\\)")," )"); 
    std::regex whitespace("\\s+");
    std::sregex_token_iterator iter(r_program.begin(),
    r_program.end(),whitespace,-1);
    std::sregex_token_iterator end;
    std::list<std::string> tokens;
    for(; iter != end; ++iter){
        tokens.push_back(*iter);
    }
    return tokens;
}

void show(std::list<std::string>  tokens){
   for(auto it = tokens.begin(); it != tokens.end(); ++it) {
      std::cout << (*it) <<"\n"; 
   }
}

Expr * read_from_tokens(std::list<std::string>& tokens){
	if(tokens.empty()){
        return NULL;
    }
    std::list<Expr*> expr;
	if(tokens.front()!="("){
		return NULL;
	}else{
       tokens.pop_front();
	}
	while(tokens.front()!=")"){
        if(tokens.front()=="("){
            Expr * exp_i = read_from_tokens(tokens);
            if(exp_i==NULL){
                return NULL;
            }
            expr.push_back(exp_i);
        }else{
            Atom * atom_i=new Atom(tokens.front());
            expr.push_back(atom_i);
            tokens.pop_front();
        }
	}
	tokens.pop_front();
	ComplexExpr * result=new ComplexExpr(expr);
	return result;
}