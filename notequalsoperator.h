#ifndef NOTEQUALSOPERATOR_H
#define NOTEQUALSOPERATOR_H

#include "binaryoperator.h"

class NotEqualsOperator : public BinaryOperator
{
public:
    NotEqualsOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~NotEqualsOperator() {}
};

#endif // NOTEQUALSOPERATOR_H
