#ifndef NONTERMINALEXPRESSION_H
#define NONTERMINALEXPRESSION_H

#include "expression.h"

class NonTerminalExpression : public Expression
{
public:
    virtual Expression *evaluate() = 0;

    virtual ~NonTerminalExpression() {}
};

#endif // NONTERMINALEXPRESSION_H

