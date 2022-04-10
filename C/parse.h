#include <variant>
#include <memory>
#ifndef PARSE
#define PARSE

typedef std::variant<float,std::string> Atom;
typedef std::shared_ptr<Atom> AtomPtr;

template<class T>
class Expr{
  public:
    std::variant<AtomPtr,std::shared_ptr<T>> data;
    bool is_atom();
    AtomPtr get_atom();
    std::shared_ptr<T> get_complex_expr();
    std::string to_str();
};

class ComplexExpr{
  public:
  std::vector<std::shared_ptr<Expr<ComplexExpr>>> subexprs;
  bool check_type(std::string type,int i=0);
  std::string to_str();
};

typedef std::shared_ptr<Expr<ComplexExpr>> ExpPtr;

typedef std::shared_ptr<Expr<ComplexExpr>> ExprPtr;
typedef std::shared_ptr<ComplexExpr> ComplexExprPtr;

ExprPtr parse_expr(const TokenSeqPtr & tokens);
AtomPtr parse_atom(const TokenPtr & token);

#endif