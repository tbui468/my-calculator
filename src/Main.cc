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
//  Let's rewrite the expression rules and base our algorithm off of that instead of just writing my intuition
//  bug: triple *|/ breaks the parser - how was this problem solved with triple +|-?
//    the problem with +|- was solved by adding in a term(left) function.  Do we need a factor(left) function?
//    or we could try to refactor out term(left) and then use that same solution with *|/ to avoid making a factor(left) function
//  Can the messiness of the parentheses code be fixed with Groups?
//  add unary operators (allow putting negative in front).  Allow double or more negatives where an even number of negatives will cancel
//  Write tests to make sure it all works when I need to refactor/add new features
//  Parser has both term(left) and term().  Can this be simplified further?
//  can this be done with unique pointers rather than all the shared pointers?

namespace myc {


class PrinterDispatcher: public AbstractDispatcher {
  public:
    std::string dispatch(Literal& literal) override {
      return std::to_string(literal.number);
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
