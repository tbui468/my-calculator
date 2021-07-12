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

//What is a token?  A token has a type, and an optional double (since we are using numbers only)
//The parser takes in a sequence of tokens and outputs the root of the abstract symbolic tree
//How is this AST constructed?  They are made by using expression rules governed by terminal and non-terminal expression
//each nonterminal Expression must have a rule associated with it.
//
//For a recursive descent parser, we order the expressions by precedence and recursively call from lowest to highest precedence
//What is an expression?  Why do we need it?  Why not just use the tokens we have already?
//What data should it contain and what functions?
//issue: a group doesn't need a token, it's just an single expression
//Literal, Binary and Group all are different - how can I make the superclass (Expr) fit them better?
//  remove Token data member and make left/right into a list of expressions?
//  TokenType operator, std::string literal (optional), std::vector<std::shared_ptr<Expr> exprs
//    Literal has 0 exprs, Group has 1 exprs, Binary has 2 exprs
//    TokenType???
//    std::string value
/*
class Group: public Expr {
  public:
    Group(std::shared_ptr<Expr> left): Expr(token, left, right) {}
    ~Binary() {}
    std::string accept(AbstractDispatcher& dispatcher) override {
      return dispatcher.dispatch(*this);
    }
  public:
}*/

}

#endif EXPR_H
