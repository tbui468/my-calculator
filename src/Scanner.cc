#include "Scanner.h"
#include <iostream>

namespace myc {


  std::vector<Token> Scanner::get_tokens() const {
    return m_tokens;
  }

  void Scanner::print_tokens() {
    for (Token t: m_tokens) {
      if (t.m_type == TokenType::NUMBER) {
        std::cout << stringify_token_type(t.m_type) << " " << std::to_string(t.m_number) << std::endl;
      }else{
        std::cout << stringify_token_type(t.m_type) << std::endl;
      }
    }
  }

  void Scanner::next() {
    while(std::isspace(m_source.at(m_current))) {
      m_current++;
      m_start = m_current;
    }
    char c = m_source.at(m_current);
    switch(c) {
      case '+':
        m_tokens.push_back(Token(TokenType::PLUS));
        break;
      case '-':
        m_tokens.push_back(Token(TokenType::MINUS));
        break;
      case '*':
        m_tokens.push_back(Token(TokenType::MULTIPLY));
        break;
      case '/':
        m_tokens.push_back(Token(TokenType::DIVIDE));
        break;
      case '(':
        m_tokens.push_back(Token(TokenType::LEFT_PAREN));
        break;
      case ')':
        m_tokens.push_back(Token(TokenType::RIGHT_PAREN));
        break;
      default:
        while(next_is_number()) {
          m_current++;
        }
        std::string s = m_source.substr(m_start, m_current - m_start + 1);
        m_tokens.push_back(Token(TokenType::NUMBER, std::stod(s)));
        break;
    }
    m_current++;
    m_start = m_current;
  }

  bool Scanner::next_is_number() {
    if (m_current + 1 >= m_source.length()) return false;
    return is_digit(m_source.at(m_current + 1));
  }

  bool Scanner::is_digit(char c) {
    return c >= '0' && c <= '9';
  }

  bool Scanner::end_of_source() {
    if (m_current >= m_source.length()) return true;
    else return false;
  }

  std::string Scanner::stringify_token_type(TokenType type) {
    switch(type) {
      case TokenType::PLUS:
        return "plus";
      case TokenType::MINUS:
        return "minus";
      case TokenType::MULTIPLY:
        return "multiply";
      case TokenType::DIVIDE:
        return "divide";
      case TokenType::LEFT_PAREN:
        return "left paren";
      case TokenType::RIGHT_PAREN:
        return "right paren";
      default:
        return "number";
    }
  }

}
