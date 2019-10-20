#ifndef CONDITION_H
#define CONDITION_H

#include "statement.h"
class Expression;

class Condition : public Statement
{
public:
    Expression *exp;
    Statement *positive;
    Statement *negative = nullptr;

    virtual void Execute();

    virtual ~Condition();
};

#endif // CONDITION_H
