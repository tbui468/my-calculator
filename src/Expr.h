#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <memory>

namespace myc {

class Literal;
class Binary;
class Group;

class AbstractDispatcher {
  public:
    virtual std::string dispatch(Literal& literal) = 0;
    virtual std::string dispatch(Binary& binary) = 0;
};

class Expr {
  public:
    Expr(double number, TokenType op, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right): number(number), op(op), left(left), right(right) {}
    virtual ~Expr() {}
    virtual std::string accept(AbstractDispatcher& dispatcher) = 0;
  public:
    double number = 0.0;
    TokenType op = TokenType::NUMBER;
    std::shared_ptr<Expr> left = nullptr;
    std::shared_ptr<Expr> right = nullptr;
};

class Literal: public Expr {
  public:
    Literal(double number): Expr(number, TokenType::NUMBER, nullptr, nullptr) {}
    ~Literal() {}
    std::string accept(AbstractDispatcher& dispatcher) override {
      return dispatcher.dispatch(*this);
    }
};

class Binary: public Expr {
  public:
    Binary(TokenType op, std::shared_ptr<Expr> left, std::shared_ptr<Expr> right): Expr(0.0, op, left, right) {}
    ~Binary() {}
    std::string accept(AbstractDispatcher& dispatcher) override {
      return dispatcher.dispatch(*this);
    }
  public:
};


}

#endif EXPR_H
