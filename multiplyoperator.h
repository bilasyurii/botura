#ifndef MULTIPLYOPERATOR_H
#define MULTIPLYOPERATOR_H

#include "binaryoperator.h"

class MultiplyOperator : public BinaryOperator
{
public:
    MultiplyOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~MultiplyOperator() {}
};

#endif // MULTIPLYOPERATOR_H
