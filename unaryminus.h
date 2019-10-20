#ifndef UNARYMINUS_H
#define UNARYMINUS_H

#include "unaryoperator.h"

class UnaryMinus : public UnaryOperator
{
public:
    UnaryMinus(Expression *e);
    virtual Expression *evaluate();

    virtual ~UnaryMinus() {}
};

#endif // UNARYMINUS_H
