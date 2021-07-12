#ifndef SCANNER_H
#define SCANNER_H


#include <vector>
#include <string>

#include "Token.h"
#include "TokenType.h"

namespace myc {

class Scanner {
  private:
    std::vector<Token> m_tokens;
    std::string m_source;
    int m_start = 0;
    int m_current = 0;
  public:
    Scanner(std::string source): m_source(source) {}
    std::vector<Token> get_tokens() const;
    void print_tokens();
    void next();
    bool next_is_number();
    bool is_digit(char c);
    bool end_of_source();
  private:
    std::string stringify_token_type(TokenType type);
};

}

#endif //SCANNER_H
