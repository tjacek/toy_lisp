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
typedef std::shared_ptr<Atom> AtomPtr;

template<class T>
class Expr{
  public:
    std::variant<AtomPtr,std::shared_ptr<T>> data;
    std::string to_str();
    bool is_atom();
};

class ComplexExpr{
  public:
  std::vector<std::shared_ptr<Expr<ComplexExpr>>> subexprs;
  std::string to_str();
};

typedef std::shared_ptr<Expr<ComplexExpr>> ExpPtr;


typedef std::shared_ptr<Expr<ComplexExpr>> ExprPtr;
typedef std::shared_ptr<ComplexExpr> ComplexExprPtr;

ExprPtr parse_expr(const TokenSeqPtr & tokens);
AtomPtr parse_atom(const TokenPtr & token);

#endif