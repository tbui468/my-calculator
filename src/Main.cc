#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"

//TODO:
//  allow parentheses - this goes at highest precedence
//  add unary operators (allow putting negative in front)
//  can this be done with unique pointers rather than all the shared pointers?

namespace myc {



//Literal, Binary, (let's skip Unary and Grouping for now)

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


//recursive descent parser
class Parser {
  public:
    std::vector<Token> m_tokens;
    size_t m_position = 0;
  public:
    Parser(std::vector<Token> tokens): m_tokens(tokens) {}
    Token previous() {
      return m_tokens.at(m_position - 1);
    }
    //extract meaning from Abstract Syntax Tree (could move this to a different class)
    double compute(std::shared_ptr<Expr> root) {
      switch (root->token.m_type) {
        case TokenType::NUMBER:
          return root->token.m_number;
          break;
        case TokenType::PLUS:
          return compute(root->left) + compute(root->right);
          break;
        case TokenType::MINUS:
          return compute(root->left) - compute(root->right);
          break;
        case TokenType::MULTIPLY:
          return compute(root->left) * compute(root->right);
          break;
        case TokenType::DIVIDE:
          return compute(root->left) / compute(root->right);
          break;
      }
    }
    std::shared_ptr<Expr> term(std::shared_ptr<Expr> left) {
      if (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        Token token = previous();
        std::shared_ptr<Expr> right = factor();
        return std::make_shared<Binary>(token, left, right);
      }else{
        return left;
      }
    }
    std::shared_ptr<Expr> term() {
      std::shared_ptr<Expr> left = factor();
      return term(left);
    }
    std::shared_ptr<Expr> factor() {
      std::shared_ptr<Expr> left = primary();
      if (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
        Token token = previous();
        std::shared_ptr<Expr> right = primary();
        return std::make_shared<Binary>(token, left, right);
      }else{
        return left;
      }
    }
    std::shared_ptr<Expr> primary() {
      if (match(TokenType::NUMBER)) {
        return std::make_shared<Literal>(previous());
        /*
      } else if (match(TokenType::LEFT_PAREN) || match(TokenType::RIGHT_PAREN)) {
        return std::make_shared<Literal>(previous());*/
      }else{
        std::cout << "Invalid syntax" << std::endl;
      }
    }
    bool match(TokenType type) {
      if (m_position >= m_tokens.size()) return false;
      if (m_tokens.at(m_position).m_type == type) {
        m_position++;
        return true;
      }else{
        return false;
      } 
    }
    bool has_tokens() const {
      return m_position < m_tokens.size();
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
    std::shared_ptr<myc::Expr> out = parser.term();
    while(parser.has_tokens()) {
      out = parser.term(out);
    }
    //use visitor pattern to print out expressions recursively
    myc::PrinterDispatcher dispatcher;
    std::cout << out->accept(dispatcher) << std::endl;
    std::cout << parser.compute(out) << std::endl;

  }

  return 0;
}
