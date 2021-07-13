set(Sources
    Main.cc
    Scanner.cc
    Token.cc
    Parser.cc
    Evaluator.cc
    )

set(Headers
    Scanner.h
    Token.h
    TokenType.h
    Parser.h
    Expr.h
    Evaluator.h
    )

add_executable(
    MyCalc
    ${Headers}
    ${Sources}
    )
