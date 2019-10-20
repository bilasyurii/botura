#ifndef FUNCTION_H
#define FUNCTION_H

#include "statement.h"
#include "statementlist.h"
#include <string>

class StatementList;

class Function : public Statement
{
public:
    std::string name;
    StatementList *statements;

    Function(std::string n, StatementList *s);

    virtual void Execute();

    virtual ~Function()
    {
        delete statements;
    }
};

#endif // FUNCTION_H
