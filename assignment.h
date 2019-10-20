#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "statement.h"
class Expression;

class Assignment : public Statement
{
public:
    Expression *left;
    Expression *right;

    Assignment(Expression *l, Expression *r);

    virtual void Execute();

    virtual ~Assignment();
};

#endif // ASSIGNMENT_H
