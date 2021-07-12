#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "Expr.h"

namespace myc {


//recursive descent parser
class Parser {
  public:
    std::vector<Token> m_tokens;
    size_t m_position = 0;
  public:
    Parser(std::vector<Token> tokens);
    Token previous();
    double compute(std::shared_ptr<Expr> root);
    std::shared_ptr<Expr> term(std::shared_ptr<Expr> left);
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> primary();
    bool match(TokenType type);
    bool has_tokens() const;
};

}

#endif //PARSER_H
