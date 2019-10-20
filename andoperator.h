#ifndef ANDOPERATOR_H
#define ANDOPERATOR_H

#include "binaryoperator.h"

class AndOperator : public BinaryOperator
{
public:
    AndOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~AndOperator() {}
};

#endif // ANDOPERATOR_H
