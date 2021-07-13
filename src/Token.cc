#include "Token.h"

namespace myc {

Token::Token(TokenType type): m_type(type) {}
Token::Token(TokenType type, double number): m_type(type), m_number(number) {}


}
