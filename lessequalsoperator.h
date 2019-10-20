#ifndef LESSEQUALSOPERATOR_H
#define LESSEQUALSOPERATOR_H

#include "binaryoperator.h"

class LessEqualsOperator : public BinaryOperator
{
public:
    LessEqualsOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~LessEqualsOperator() {}
};

#endif // LESSEQUALSOPERATOR_H
