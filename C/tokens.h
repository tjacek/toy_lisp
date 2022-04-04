#ifndef MATH
#define MATH

enum TokenType {SYNTAX,NUMBER,VAR,STRING};

class Token{
  public:
    TokenType type;
    std::string data;
    Token(TokenType type,std::string str);
};

class TokenSeq{
  private:
    std::vector<TokenPtr> tokens;
    int current=0;

  public:
  	print(int i=0);
  	void print_types();
};

typedef std::shared_ptr<TokenSeq> TokenSeqPtr;
TokenSeqPtr tokenize(std::string line);

#endif