#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <memory>

namespace myc {

class Literal;
class Binary;

class AbstractDispatcher {
  public:
    virtual std::string dispatch(Literal& literal) = 0;
    virtual std::string dispatch(Binary& binary) = 0;
};

class Expr {
  public:
    Expr(Token token, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right): token(token), left(left), right(right) {}
    virtual ~Expr() {}
    virtual std::string accept(AbstractDispatcher& dispatcher) = 0;
  public:
    Token token; 
    std::shared_ptr<Expr> left;
    std::shared_ptr<Expr> right;
};

class Literal: public Expr {
  public:
    Literal(Token token): Expr(token, nullptr, nullptr) {}
    ~Literal() {}
    std::string accept(AbstractDispatcher& dispatcher) override {
      return dispatcher.dispatch(*this);
    }
};

class Binary: public Expr {
  public:
    Binary(Token token, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right): Expr(token, left, right) {}
    ~Binary() {}
    std::string accept(AbstractDispatcher& dispatcher) override {
      return dispatcher.dispatch(*this);
    }
  public:
};

}

#endif EXPR_H
