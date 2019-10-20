#ifndef MINUSOPERATOR_H
#define MINUSOPERATOR_H

#include "binaryoperator.h"

class MinusOperator : public BinaryOperator
{
public:
    MinusOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~MinusOperator() {}
};

#endif // MINUSOPERATOR_H
