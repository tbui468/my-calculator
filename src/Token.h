#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TokenType.h"

namespace myc {

class Token {
  public:
    TokenType m_type;
    double m_number;
  public:
    Token(TokenType type);
    Token(TokenType type, double number);
};

}

#endif //TOKEN_H
