#include <string>
#include <iostream>
#include <regex>
#include <list>
#include <map>
#ifndef LISP
#define LISP
using namespace std;

enum class ObjectType{number_type,string_type,operator_type};

class Object;

typedef std::map<std::string,Object*> Envir;

class Object{
    public:
        ObjectType type;
        virtual Object * eval(Envir envir);
        virtual Object * call(std::list<Object*> args,Envir envir);
        virtual std::string to_str();
        virtual bool to_bool();
};

class NumberObject: public Object{
   public:
       ObjectType type=ObjectType::number_type;
       NumberObject(float value);
       float value;
       std::string to_str();
       bool to_bool();
};

class StringObject:public Object{
   public:
       ObjectType type=ObjectType::string_type;
       StringObject(std::string value);
       string value;
       std::string to_str();
};

enum class ExprType{atom_type,complex_type};

class Expr{
    public:
      ExprType type;
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

class ComplexExpr: public Expr{
	public:
    	std::list<Expr*> value;
    	ComplexExpr(std::list<Expr*> value);
    	virtual void show();
        int size();
};

std::list<std::string> tokenize(std::string program);
void show(std::list<std::string>  tokens);
Expr * read_from_tokens(std::list<std::string> &);
#endif