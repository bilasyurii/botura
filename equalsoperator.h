#ifndef EQUALSOPERATOR_H
#define EQUALSOPERATOR_H

#include "binaryoperator.h"

class EqualsOperator : public BinaryOperator
{
public:
    EqualsOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~EqualsOperator() {}
};

#endif // EQUALSOPERATOR_H
