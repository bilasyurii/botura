#ifndef GREATEREQUALSOPERATOR_H
#define GREATEREQUALSOPERATOR_H

#include "binaryoperator.h"

class GreaterEqualsOperator : public BinaryOperator
{
public:
    GreaterEqualsOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~GreaterEqualsOperator() {}
};

#endif // GREATEREQUALSOPERATOR_H
