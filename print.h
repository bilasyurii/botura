#ifndef PRINT_H
#define PRINT_H

#include "statement.h"
class Expression;

class Print : public Statement
{
public:
    Expression *exp;

    Print(Expression *e);

    virtual void Execute();

    virtual ~Print()
    {
        delete exp;
    }
};

#endif // PRINT_H
