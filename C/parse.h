#include <variant>
#ifndef PARSE
#define PARSE

typedef std::variant<std::string,float> Atom;

template<class T>
using Expr = std::variant<Atom,T>;

class ComplexExpr{
  public:
  std::vector<Expr<ComplexExpr>> subexprs;
};

#endif