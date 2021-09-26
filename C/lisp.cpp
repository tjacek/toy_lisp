#include "lisp.h"

std::vector<std::string> tokenize(std::string program){
    auto l_program=regex_replace(program,regex("\\("),"( ");   
    auto r_program=regex_replace(l_program,regex("\\)")," )"); 
    std::regex whitespace("\\s+");
    std::sregex_token_iterator iter(r_program.begin(),
    r_program.end(),whitespace,-1);
    std::sregex_token_iterator end;
    std::vector<std::string> tokens;
    for(; iter != end; ++iter){
        tokens.push_back(*iter);
    }
    return tokens;
}

void show(std::vector<std::string>  tokens){
   for(auto it = tokens.begin(); it != tokens.end(); ++it) {
      std::cout << (*it) <<"\n"; 
   }
}

int main(){
	std::string program = "(begin (define r 10) (* pi (* r r)))";
    auto tokens=tokenize(program);
    show(tokens);
}