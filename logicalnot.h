#ifndef LOGICALNOT_H
#define LOGICALNOT_H

#include "unaryoperator.h"

class LogicalNot : public UnaryOperator
{
public:
    LogicalNot(Expression *e);

    virtual Expression *evaluate();

    virtual ~LogicalNot() {}
};

#endif // LOGICALNOT_H
