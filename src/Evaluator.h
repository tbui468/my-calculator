#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <memory>
#include <string>
#include "Expr.h"

namespace myc {


  class PrinterDispatcher: public AbstractDispatcher {
    public:
      std::string dispatch(Literal& literal) override {
        return std::to_string(literal.number);
      } 
      std::string dispatch(Unary& unary) override {
        return "(-" + unary.left->accept(*this) + ")";
      }
      std::string dispatch(Binary& binary) override {
        std::string op = "";
        switch(binary.op) {
          case TokenType::PLUS: op = "+"; break;
          case TokenType::MINUS: op = "-"; break;
          case TokenType::MULTIPLY: op = "*"; break;
          default: op = "/"; break;
        }
        return "(" + binary.left->accept(*this) + " " + op + " " + binary.right->accept(*this) + ")";
      } 
  };

  class Evaluator {
    public:
      Evaluator();
      std::string get_string(std::shared_ptr<Expr> root) const;
      double compute(std::shared_ptr<Expr> root) const;
    private:
  };

}

#endif //EVALUATOR
