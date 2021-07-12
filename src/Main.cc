#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "Expr.h"
#include "Parser.h"

//TODO:
//  allow parentheses - this goes at highest precedence
//  add unary operators (allow putting negative in front)
//  can this be done with unique pointers rather than all the shared pointers?

namespace myc {


class PrinterDispatcher: public AbstractDispatcher {
  public:
    std::string dispatch(Literal& literal) override {
      return std::to_string(literal.token.m_number);
    } 
    std::string dispatch(Binary& binary) override {
      std::string op = "";
      switch (binary.token.m_type) {
        case TokenType::PLUS:     op = "+"; break;
        case TokenType::MINUS:    op = "-"; break;
        case TokenType::MULTIPLY: op = "*"; break;
        case TokenType::DIVIDE:   op = "/"; break;
      }

      return "(" + binary.left->accept(*this) + " " + op + " " + binary.right->accept(*this) + ")";
    } 
};

}

int main(int argc, char** argv) {

  if (argc > 1) {
    std::cout << "Usage: MyCalc" << std::endl;
    return 1;
  }

  std::string input;

  while(true) {
    std::cout << "> ";
    std::getline(std::cin, input);
    if (input == "quit()") {
      break;
    }

    //get list of tokens
    myc::Scanner scanner = myc::Scanner(input);
    while (!scanner.end_of_source()) {
      scanner.next();
    }
    scanner.print_tokens();

    myc::Parser parser = myc::Parser(scanner.get_tokens());
    std::shared_ptr<myc::Expr> out = parser.expression();
    //use visitor pattern to print out expressions recursively
    myc::PrinterDispatcher dispatcher;
    std::cout << out->accept(dispatcher) << std::endl;
    std::cout << parser.compute(out) << std::endl;

  }

  return 0;
}
