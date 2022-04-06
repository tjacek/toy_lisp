#include <variant>
#include <memory>
#ifndef PARSE
#define PARSE

/*class Expr{
  public:
    bool is_atom;

};

typedef std::shared_ptr<Expr> ExprPtr;

class Atom:Expr{
  public:
    std::variant<std::string,float> data;
};

class ComplexExpr:Expr{
  public:
  std::vector<ExprPtr> subexpr; 
};*/

typedef std::variant<std::string,float> Atom;

template<class T>
class Expr{
  public:
    std::variant<std::shared_ptr<Atom>,std::shared_ptr<T>> data;
};

class ComplexExpr{
  public:
  std::vector<Expr<ComplexExpr>> subexprs;
};

typedef std::shared_ptr<Expr<ComplexExpr>> ExprPtr;
typedef std::shared_ptr<ComplexExpr> ComplexExprPtr;

ExprPtr parse_expr(const TokenSeqPtr & tokens);
//AtomPtr parse_atom(const TokenPtr & token);

#endif