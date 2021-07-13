
#include <iostream>
#include "Parser.h"

namespace myc {

  Parser::Parser(std::vector<Token> tokens): m_tokens(tokens) {}

  Token Parser::previous() {
    return m_tokens.at(m_position - 1);
  }

  //split this off to a differnt class to evaluate AST
  double Parser::compute(std::shared_ptr<Expr> root) {
    switch (root->op) {
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
      default:
        return root->number;
        break;
    }
  }

  std::shared_ptr<Expr> Parser::expression() {
    return term();
  }

  std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> left = factor();
    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
      Token token = previous();
      std::shared_ptr<Expr> right = factor();
      left = std::make_shared<Binary>(token.m_type, left, right);
    }

    return left;
  }

  std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> left = unary();
    while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
      Token token = previous();
      std::shared_ptr<Expr> right = unary();
      left = std::make_shared<Binary>(token.m_type, left, right); 
    }

    return left;
  }

  std::shared_ptr<Expr> Parser::unary() {
    if (match(TokenType::MINUS)) {
      Token token = previous();       
      std::shared_ptr<Expr> left = unary();
      return std::make_shared<Unary>(token.m_type, left);
    } else {
      return primary();
    }
  }

  std::shared_ptr<Expr> Parser::primary() {
    if (match(TokenType::NUMBER)) {
      return std::make_shared<Literal>(previous().m_number);
    }

    if (match(TokenType::LEFT_PAREN)) {
      std::shared_ptr<Expr> expr = expression();
      if (match(TokenType::RIGHT_PAREN)) {
        return expr;
      } else {
        std::cout << "Failed to close parentheses" << std::endl;
      }
    }

    std::cout << "Invalid syntax" << std::endl;
  }

  bool Parser::match(TokenType type) {
    if (m_position >= m_tokens.size()) return false;
    if (m_tokens.at(m_position).m_type == type) {
      m_position++;
      return true;
    }else{
      return false;
    } 
  }

  bool Parser::has_tokens() const {
    return m_position < m_tokens.size();
  }

}
