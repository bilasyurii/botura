#ifndef PARSER_H
#define PARSER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "token.h"
class BotControl;
class WhileLoop;
class StatementList;
class Statement;
class Expression;
class Condition;
class Raise;
class Print;
class World;

class Parser
{
    unsigned current;
    unsigned size;
    unsigned braceCount;
    void splitToTokens(std::string str);
    World &world;
    sf::Mutex &mutex;
    StatementList *parseToTree();
    Expression *parseExpression();
    Statement *parseSingleCommand();
    Condition *parseIf();
    WhileLoop *parseWhile();
    BotControl *parseMove();
    BotControl *parseTurnLeft();
    BotControl *parseTurnRight();
    BotControl *parseJump();
    BotControl *parseStand();
    Statement *parseVar();
    Print *parsePrint();
    Raise *parseRaise();
    void parseFunction();
    unsigned getPrecedence(std::string op) const;
    void addNodeToTree(std::vector<Expression*> &tree, std::string op);
    void checkToken(Token t);
public:
    std::vector<Token> tokens;
    StatementList *first;
    Parser(World &w);
    std::string analyse(std::string str);
    void Execute();
    static std::string readFromFile(std::string path);
};

#endif // PARSER_H
