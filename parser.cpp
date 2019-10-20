#include "parser.h"

#include "world.h"
#include "statementlist.h"
#include <iostream>
#include "raise.h"
#include "plusoperator.h"
#include "minusoperator.h"
#include "multiplyoperator.h"
#include "divideoperator.h"
#include "modulooperator.h"
#include "andoperator.h"
#include "oroperator.h"
#include "equalsoperator.h"
#include "lessthanoperator.h"
#include "greaterthanoperator.h"
#include "notequalsoperator.h"
#include "lessequalsoperator.h"
#include "greaterequalsoperator.h"
#include "logicalnot.h"
#include "unaryminus.h"
#include "variable.h"
#include "literal.h"
#include "stringoperations.h"
#include "data.h"
#include "databank.h"
#include "declaration.h"
#include "initialization.h"
#include "print.h"
#include "function.h"
#include "event.h"
#include "assignment.h"
#include "functioncall.h"
#include "condition.h"
#include "botcontrol.h"
#include "whileloop.h"
#include "scopecontrol.h"
#include <fstream>

Parser::Parser(World &w) : braceCount(0), world(w), mutex(w.mutex)
{
    world.mutex.lock();
}

void Parser::Execute()
{
    try
    {
        first->Execute();
        delete first;
    }
    catch(...)
    {
        std::cout << "\nThere were errors during execution.\n";
    }
    world.actionSlot = World::END;
    world.mutex.unlock();
}

std::string Parser::analyse(std::string str)
{
    current = 0;
    braceCount = 0;
    splitToTokens(str);
    size = tokens.size();
    Token tok = tokens[0];
    if(tok.type == Token::KEYWORD && tok.data == "load")
    {
        tok = tokens[1];
        if(tok.type != Token::STRING)
        {
            std::cout << "Error: expected string after 'load' keyword.\n";
            throw 0;
        }
        current += 2;
        checkToken(Token { Token::PUNCTUAL, ";" });
    }
    else
        tok.data = "res/01.btr";
    first = parseToTree();
    first->statements.push_back(new Raise("END"));
    return tok.data;
}

unsigned Parser::getPrecedence(std::string op) const
{
    if(op == "u-" || op == "!")
        return 0;
    if(op == "*" || op == "/" || op == "%")
        return 1;
    if(op == "+" || op == "-")
        return 2;
    if(op == "<" || op == ">" || op == "<=" || op == ">=")
        return 3;
    if(op == "==" || op == "!=")
        return 4;
    if(op == "&&")
        return 5;
    if(op == "||")
        return 6;
    if(op == "=")
        return 7;
    return 99;
}

void Parser::addNodeToTree(std::vector<Expression*>& tree, std::string op)
{
    Expression *one, *two, *result;
    if(op == "+")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new PlusOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "-")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new MinusOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "*")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new MultiplyOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "/")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new DivideOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "%")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new ModuloOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "&&")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new AndOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "||")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new OrOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "==")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new EqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "<")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new LessThanOperator(one, two);
        tree.push_back(result);
    }
    else if(op == ">")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new GreaterThanOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "!=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new NotEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "<=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new LessEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == ">=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new GreaterEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "!")
    {
        one = tree.back();
        tree.pop_back();
        result = new LogicalNot(one);
        tree.push_back(result);
    }
    else if(op == "u-")
    {
        one = tree.back();
        tree.pop_back();
        result = new UnaryMinus(one);
        tree.push_back(result);
    }
}

Expression *Parser::parseExpression()
{
    Token token;
    std::vector<Expression*> tree;
    std::vector<std::string> operators;
    unsigned parenthesesCount = 0;
    bool possibleUnaryMinus = true;
    while(current < size)
    {
        token = tokens[current];
        if(token.type == Token::OPERATOR)
        {
            if(possibleUnaryMinus && token.data == "-")
            {
                possibleUnaryMinus = false;
                token.data = "u-";
            }
            else
                possibleUnaryMinus = true;
            while(!operators.empty())
            {
                if(operators.back() != "(" && getPrecedence(token.data) >=
                                              getPrecedence(operators.back()))
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                else
                    break;
            }
            operators.push_back(token.data);
        }
        else if(token.type == Token::PUNCTUAL)
        {
            if(token.data == ";")
            {
                while(!operators.empty())
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                return tree[0];
            }
            else if(token.data == "(")
            {
                operators.push_back(token.data);
                ++parenthesesCount;
                possibleUnaryMinus = true;
            }
            else if(token.data == ")")
            {
                if(parenthesesCount == 0)
                {
                    while(!operators.empty())
                    {
                        addNodeToTree(tree, operators.back());
                        operators.pop_back();
                    }
                    return tree[0];
                }
                --parenthesesCount;
                possibleUnaryMinus = false;
                while(operators.back() != "(")
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                operators.pop_back();
            }
        }
        else
        {
            if(token.type == Token::IDENTIFIER)
                tree.push_back(new Variable(token.data));
            else if(token.type == Token::NUMBER)
                tree.push_back(new Literal(new Data("", StringToInt(token.data))));
            else if(token.type == Token::BOOLEAN)
                tree.push_back(new Literal(new Data("", StringToBoolean(token.data))));
            else if(token.type == Token::FLOAT)
                tree.push_back(new Literal(new Data("", StringToFloat(token.data))));
            else if(token.type == Token::STRING)
                tree.push_back(new Literal(new Data("", token.data)));
            else if(token.type == Token::PNULL)
                tree.push_back(new Literal(new Data("")));
            else
            {
                std::cout << "Error: not expected keyword.\n";
                throw 0;
            }
            possibleUnaryMinus = false;
        }
        ++current;
    }
    std::cout << "Error: not expected end of file.\n";
    throw 0;
}

void Parser::checkToken(Token t)
{
    Token token = tokens[current];
    if(token.type == t.type && token.data == t.data)
        ++current;
    else
    {
        std::cout << "Error: '" << t.data << "' expected.\n";
        throw 0;
    }
}

Statement *Parser::parseVar()
{
    ++current;
    Token name = tokens[current];
    if(name.type != Token::IDENTIFIER)
    {
        std::cout << "Error: identifier expected.\n";
        throw 0;
    }
    if(bank.isDeclared(name.data))
    {
        std::cout << "Error: redeclaration of" << name.data << ".\n";
        throw 0;
    }
    ++current;
    Token nextToken = tokens[current];
    if(nextToken.type == Token::PUNCTUAL && nextToken.data == ";")
    {
        ++current;
        return new Declaration(name.data);
    }
    else if(nextToken.type == Token::OPERATOR && nextToken.data == "=")
    {
        Statement *stat = new Initialization(name.data, parseExpression());
        checkToken(Token { Token::PUNCTUAL, ";" });
        return stat;
    }
    else
    {
        std::cout << "Error: expected '=' or ';' after declaration.\n";
        throw 0;
    }
}

Print *Parser::parsePrint()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Print *statement = new Print(parseExpression());
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return statement;
}

Raise *Parser::parseRaise()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Token token = tokens[current];
    if(token.type != Token::IDENTIFIER)
    {
        std::cout << "Error: event identifier expected after keyword 'raise'.\n";
        throw 0;
    }
    Raise *raise = new Raise(token.data);
    ++current;
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return raise;
}

void Parser::parseFunction()
{
    if(braceCount > 0)
    {
        std::cout << "Error: functions can only be created in global scope.\n";
        throw 0;
    }
    ++current;
    Token token = tokens[current];
    if(token.type != Token::IDENTIFIER)
    {
        std::cout << "Error: identifier expected after keyword 'function'.\n";
        throw 0;
    }
    ++current;
    Token tok = tokens[current];
    Function *func;
    if(tok.type == Token::PUNCTUAL && tok.data == "{")
    {
        ++braceCount;
        ++current;
        if(bank.isFunctionDeclared(token.data))
        {
            std::cout << "Error: function " << token.data << " was already declared.\n";
            throw 0;
        }
        func = new Function(token.data, parseToTree());
    }
    else if(tok.type == Token::KEYWORD && tok.data == "listen")
    {
        ++current;
        tok = tokens[current];
        if(tok.type != Token::IDENTIFIER)
        {
            std::cout << "Error: event identifier expected after keyword 'listen'.\n";
            throw 0;
        }
        ++current;
        checkToken(Token { Token::PUNCTUAL, "{" });
        ++braceCount;
        if(bank.isFunctionDeclared(token.data))
        {
            std::cout << "Error: function " << token.data << " was already declared.\n";
            throw 0;
        }
        func = new Function(token.data, parseToTree());
        if(!bank.isEventDeclared(tok.data))
            bank.declare(tok.data, new Event);
        bank.getEvent(tok.data)->listeners.push_back(func);    }
    bank.declare(token.data, func);
}

Statement *Parser::parseSingleCommand()
{
    Token token;
    Statement *statement = nullptr;
    token = tokens[current];
    switch(token.type)
    {
    case Token::IDENTIFIER:
        {
            ++current;
            Token tok = tokens[current];
            if(tok.type == Token::OPERATOR)
            {
                if(tok.data == "=")
                {
                    ++current;
                    statement = new Assignment(new Variable(token.data),
                                               parseExpression());
                    checkToken(Token { Token::PUNCTUAL, ";" });
                }
                else
                {
                    std::cout << "Error: operator expected.\n";
                    throw 0;
                }
            }
            else if(tok.type == Token::PUNCTUAL && tok.data == "(")
            {
                ++current;
                checkToken(Token { Token::PUNCTUAL, ")" });
                checkToken(Token { Token::PUNCTUAL, ";" });
                statement = new FunctionCall(token.data);
            }
            else
            {
                std::cout << "Error: operator expected.\n";
                throw 0;
            }
            break;
        }
    case Token::KEYWORD:
        {
            if(token.data == "var")
            {
                std::cout << "Error: single command can't be a declaration or an initialization.\n";
                throw 0;
            }
            else if(token.data == "if")
                statement = parseIf();
            else if(token.data == "while")
                statement = parseWhile();
            else if(token.data == "move")
                statement = parseMove();
            else if(token.data == "turnLeft")
                statement = parseTurnLeft();
            else if(token.data == "turnRight")
                statement = parseTurnRight();
            else if(token.data == "jump")
                statement = parseJump();
            else if(token.data == "stand")
                statement = parseStand();
            else if(token.data == "print")
                statement = parsePrint();
            else if(token.data == "raise")
                statement = parseRaise();
            else if(token.data == "function")
            {
                std::cout << "Error: single command can't be a function declaration.\n";
                throw 0;
            }
            break;
        }
    default:
        {
            std::cout << "Error: identifier or keyword expected.\n";
            throw 0;
        }
    }
    return statement;
}

Condition *Parser::parseIf()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Condition *condition = new Condition;
    condition->exp = parseExpression();
    checkToken(Token { Token::PUNCTUAL, ")" });
    Token token = tokens[current];
    if(token.type == Token::PUNCTUAL && token.data == "{")
    {
        ++current;
        ++braceCount;
        condition->positive = parseToTree();
    }
    else
        condition->positive = parseSingleCommand();
    if(current >= size)
        return condition;
    token = tokens[current];
    if(token.type == Token::KEYWORD && token.data == "else")
    {
        ++current;
        if(current >= size)
            return condition;
        token = tokens[current];
        if(token.type == Token::PUNCTUAL && token.data == "{")
        {
            ++current;
            ++braceCount;
            if(current >= size)
                return condition;
            condition->negative = parseToTree();
        }
        else
            condition->negative = parseSingleCommand();
    }
    return condition;
}

WhileLoop *Parser::parseWhile()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    WhileLoop *loop = new WhileLoop;
    loop->exp = parseExpression();
    checkToken(Token { Token::PUNCTUAL, ")" });
    Token token = tokens[current];
    if(token.type == Token::PUNCTUAL && token.data == "{")
    {
        ++current;
        ++braceCount;
        loop->action = parseToTree();
    }
    else
        loop->action = parseSingleCommand();
    return loop;
}

BotControl *Parser::parseMove()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::MOVE);
}

BotControl *Parser::parseTurnLeft()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::TURN_LEFT);
}

BotControl *Parser::parseTurnRight()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::TURN_RIGHT);
}

BotControl *Parser::parseJump()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::JUMP);
}

BotControl *Parser::parseStand()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::STAND);
}

StatementList *Parser::parseToTree()
{
    Token token;
    StatementList *statements = new StatementList;
    bool scopeCreated = false;
    while(current < size)
    {
        token = tokens[current];
        switch(token.type)
        {
        case Token::IDENTIFIER:
            statements->statements.push_back(parseSingleCommand());
            break;
        case Token::KEYWORD:
            {
                if(token.data == "var")
                {
                    if(!scopeCreated)
                    {
                        statements->statements.push_back(
                            new ScopeControl(ScopeControl::CREATE));
                        scopeCreated = true;
                    }
                    statements->statements.push_back(parseVar());
                }
                else if(token.data == "if")
                    statements->statements.push_back(parseIf());
                else if(token.data == "while")
                    statements->statements.push_back(parseWhile());
                else if(token.data == "print")
                    statements->statements.push_back(parsePrint());
                else if(token.data == "move")
                    statements->statements.push_back(parseMove());
                else if(token.data == "turnLeft")
                    statements->statements.push_back(parseTurnLeft());
                else if(token.data == "turnRight")
                    statements->statements.push_back(parseTurnRight());
                else if(token.data == "jump")
                    statements->statements.push_back(parseJump());
                else if(token.data == "stand")
                    statements->statements.push_back(parseStand());
                else if(token.data == "function")
                    parseFunction();
                else if(token.data == "raise")
                    statements->statements.push_back(parseRaise());
            }
            break;
        case Token::PUNCTUAL:
            {
                if(token.data == "}")
                {
                    if(braceCount == 0)
                    {
                        std::cout << "Error: not expected '}'.\n";
                        throw 0;
                    }
                    else
                    {
                        --braceCount;
                        ++current;
                        if(scopeCreated)
                            statements->statements.push_back(
                                new ScopeControl(ScopeControl::DELETE));
                        return statements;
                    }
                }
                else
                {
                    std::cout << "Error: not expected '" << token.data << "'.\n";
                    throw 0;
                }
            }
            break;
        default:
            {
                std::cout << "Error: identifier or keyword expected.\n";
                throw 0;
            }
        }
    }
    if(scopeCreated)
        statements->statements.push_back(
            new ScopeControl(ScopeControl::DELETE));
    return statements;
}

void Parser::splitToTokens(std::string str)
{
    char symbol;
    std::string token;
    unsigned i = 0;
    bool isFirstDot;
    unsigned strSize = str.size();
    while(i < strSize)
    {
        symbol = str[i];
        token = symbol;
        if(symbol == ' ' || symbol == '\t')
        {
            ++i;
        }
        else if(isDigit(symbol))
        {
            ++i;
            isFirstDot = true;
            while(i < strSize)
            {
                symbol = str[i];
                if(isDigit(symbol) || symbol == '.')
                {
                    token += symbol;
                    if(symbol == '.')
                    {
                        if(isFirstDot)
                            isFirstDot = false;
                        else
                        {
                            std::cout << "Error: not expected '.'.\n";
                            throw 0;
                        }
                    }
                    else if(token[0] == '0' && token[1] == '0')
                    {
                        std::cout << "Error: not expected '0'.\n";
                        throw 0;
                    }
                }
                else if(symbol == ' ' || symbol == '\t' || isOperator(symbol) || isPunctual(symbol))
                {
                    if(token.back() == '.')
                    {
                        std::cout << "Error: float can't have a dot in the end.\n";
                        throw 0;
                    }
                    if(isFirstDot)
                        tokens.push_back(Token { Token::NUMBER, token });
                    else
                        tokens.push_back(Token { Token::FLOAT, token });
                    break;
                }
                else
                {
                    std::cout << "Error: not expected symbol '" << symbol << "'.\n";
                    throw 0;
                }
                ++i;
            }
        }
        else if(isLetter(symbol))
        {
            ++i;
            while(i < strSize)
            {
                symbol = str[i];
                if(isLetter(symbol) || isDigit(symbol))
                    token += symbol;
                else
                {
                    if(token == "var" || token == "if" ||
                       token == "while" || token == "load" ||
                       token == "function" || token == "print" ||
                       token == "else" || token == "stand" ||
                       token == "move" || token == "turnLeft" ||
                       token == "turnRight" || token == "jump" ||
                       token == "listen" || token == "raise"
                    /* token == "break" ||
                       token == "continue" || token == "return" ||*/)
                        tokens.push_back(Token { Token::KEYWORD, token });
                    else if(token == "true" || token == "false")
                        tokens.push_back(Token { Token::BOOLEAN, token});
                    else if(token == "null")
                        tokens.push_back(Token { Token::PNULL, ""});
                    else
                        tokens.push_back(Token { Token::IDENTIFIER, token });
                    break;
                }
                ++i;
            }
        }
        else if(isPunctual(symbol))
        {
            tokens.push_back(Token { Token::PUNCTUAL, token });
            ++i;
        }
        else if(isOperator(symbol))
        {
            ++i;
            symbol = str[i];
            if(token == "/" && symbol == '*')
            {
                i+=2;
                while(i < strSize)
                {
                    if(str[i] == '/' && str[i - 1] == '*')
                        break;
                    else
                        ++i;
                }
                if(i < strSize)
                    ++i;
                else
                {
                    std::cout << "Error: not found end of comment.\n";
                    throw 0;
                }
            }
            else if(isOperator(symbol))
            {
                token += symbol;
                if(token == "==" || token == "!=" ||
                   token == "<=" || token == ">=" ||
                   token == "+=" || token == "-=" ||
                   token == "*=" || token == "/=" ||
                   token == "&&" || token == "||")
                {
                    tokens.push_back(Token { Token::OPERATOR, token });
                    ++i;
                }
                else
                {
                    token.pop_back();
                    tokens.push_back(Token { Token::OPERATOR, token });
                }
            }
            else if(token != "&" && token != "|")
                tokens.push_back(Token { Token::OPERATOR, token });
        }
        else if(symbol == '\"')
        {
            ++i;
            token = "";
            while(i < strSize)
            {
                symbol = str[i];
                if(symbol == '\"')
                {
                    ++i;
                    tokens.push_back(Token { Token::STRING, token });
                    break;
                }
                else if(symbol == '\\')
                {
                    ++i;
                    symbol = str[i];
                    switch(symbol)
                    {
                    case 'n':
                        token += '\n';
                        break;
                    case '\\':
                        token += '\\';
                        break;
                    case 't':
                        token += '\t';
                        break;
                    case '\"':
                        token += '\"';
                        break;
                    }
                    ++i;
                }
                else
                {
                    token += symbol;
                    ++i;
                }
            }
        }
        else
        {
            std::cout << "Error: not expected '" << symbol << "'.\n";
            throw 0;
        }
    }
}

std::string Parser::readFromFile(std::string path)
{
    std::ifstream fin;
    fin.open(path);
    std::string temp, code;
    bool empty = true;
    while(std::getline(fin, temp))
    {
        if(empty)
            empty = false;
        else
            code += " ";
        code += temp;
    }
    fin.close();
    return code;
}
