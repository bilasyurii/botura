#ifndef TERMINALEXPRESSION_H
#define TERMINALEXPRESSION_H

#include "expression.h"

class Data;

class TerminalExpression : public Expression
{
public:
    virtual Expression *evaluate();
    virtual Data *getData() = 0;
};

#endif // TERMINALEXPRESSION_H
