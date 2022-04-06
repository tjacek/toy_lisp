#include "tokens.h"

void interpret(std::string in_path){
  std::ifstream infile(in_path);
  std::string line;
  std::vector<TokenSeqPtr> lines;
  int line_counter=0;
  while (std::getline(infile, line)){
    line_counter++;
    TokenSeqPtr tokens= tokenize(line);
    tokens->print_types();
    tokens->peek();
    tokens->shift();
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

int main(){
  interpret("test.lisp");
}