#ifndef PLUSOPERATOR_H
#define PLUSOPERATOR_H

#include "binaryoperator.h"

class PlusOperator : public BinaryOperator
{
public:
    PlusOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~PlusOperator() {}
};

#endif // PLUSOPERATOR_H
