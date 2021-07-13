#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "Expr.h"
#include "Parser.h"
#include "Evaluator.h"

//TODO:
//  Write tests to make sure it all works when I need to refactor/add new features
//  can this be done with unique pointers rather than all the shared pointers?


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
    std::shared_ptr<myc::Expr> root = parser.expression();


    myc::Evaluator ev = myc::Evaluator();
    std::cout << ev.get_string(root) << std::endl;

    std::cout << ev.compute(root) << std::endl;

  }

  return 0;
}
