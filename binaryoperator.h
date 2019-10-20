#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H

#include "nonterminalexpression.h"

class BinaryOperator : public NonTerminalExpression
{
public:
    Expression *left;
    Expression *right;

    BinaryOperator(Expression *l, Expression *r);

    virtual Expression *evaluate() = 0;

    virtual ~BinaryOperator();
};

#endif // BINARYOPERATOR_H
