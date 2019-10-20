#ifndef LESSTHANOPERATOR_H
#define LESSTHANOPERATOR_H

#include "binaryoperator.h"

class LessThanOperator : public BinaryOperator
{
public:
    LessThanOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~LessThanOperator() {}
};

#endif // LESSTHANOPERATOR_H
