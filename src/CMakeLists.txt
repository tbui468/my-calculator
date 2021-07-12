set(Sources
    Main.cc
    Scanner.cc
    Token.cc
    )

set(Headers
    Scanner.h
    Token.h
    TokenType.h
    )

add_executable(
    MyCalc
    ${Headers}
    ${Sources}
    )
