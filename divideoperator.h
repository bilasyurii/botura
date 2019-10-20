#ifndef DIVIDEOPERATOR_H
#define DIVIDEOPERATOR_H

#include "binaryoperator.h"

class DivideOperator : public BinaryOperator
{
public:
    DivideOperator(Expression *l, Expression *r);
    virtual Expression *evaluate();

    virtual ~DivideOperator() {}
};

#endif // DIVIDEOPERATOR_H
