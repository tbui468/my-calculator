set(Sources
    Main.cc
    Scanner.cc
    Token.cc
    Parser.cc
    )

set(Headers
    Scanner.h
    Token.h
    TokenType.h
    Parser.h
    Expr.h
    )

add_executable(
    MyCalc
    ${Headers}
    ${Sources}
    )
