#include <string>
#include <iostream>
#include <regex>
#include <list>

using namespace std;

class Expr{
    public:
      virtual void show()=0;
      virtual int size()=0;
};

class Atom:public Expr{
    public:
    	std::string value;
    	Atom(std::string value);
    	void show();
        int size();
};

class ProperExpr: public Expr{
	public:
    	std::list<Expr*> value;
    	ProperExpr(std::list<Expr*> value);
    	virtual void show();
        int size();
};

std::list<std::string> tokenize(std::string program);
void show(std::list<std::string>  tokens);
Expr * read_from_tokens(std::list<std::string> &);