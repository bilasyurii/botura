#ifndef WHILELOOP_H
#define WHILELOOP_H

#include "statement.h"
class Expression;

class WhileLoop : public Statement
{
public:
    Expression *exp;
    Statement *action;

    virtual void Execute();

    virtual ~WhileLoop();
};

#endif // WHILELOOP_H
