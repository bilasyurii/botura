#ifndef GREATERTHANOPERATOR_H
#define GREATERTHANOPERATOR_H

#include "binaryoperator.h"

class GreaterThanOperator : public BinaryOperator
{
public:
    GreaterThanOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~GreaterThanOperator() {}
};

#endif // GREATERTHANOPERATOR_H
