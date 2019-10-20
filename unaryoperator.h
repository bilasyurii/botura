#ifndef UNARYOPERATOR_H
#define UNARYOPERATOR_H

#include "nonterminalexpression.h"

class Expression;

class UnaryOperator : public NonTerminalExpression
{
public:
    Expression *expr;

    UnaryOperator(Expression *e) : expr(e) {}

    virtual Expression *evaluate() = 0;

    virtual ~UnaryOperator()
    {
        delete expr;
    }
};

#endif // UNARYOPERATOR_H


