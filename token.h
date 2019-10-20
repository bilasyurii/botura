#ifndef TOKEN_H
#define TOKEN_H

struct Token
{
    enum TokenType
    {
        IDENTIFIER,
        KEYWORD,
        NUMBER,
        FLOAT,
        STRING,
        OPERATOR,
        PUNCTUAL,
        BOOLEAN,
        PNULL
    };
    TokenType type;
    std::string data;
};

#endif // TOKEN_H

