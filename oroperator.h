#ifndef OROPERATOR_H
#define OROPERATOR_H

#include "binaryoperator.h"

class OrOperator : public BinaryOperator
{
public:
    OrOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~OrOperator() {}
};

#endif // OROPERATOR_H
