#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "declaration.h"
class Expression;

class Initialization : public Declaration
{
public:
    Expression *exp;

    Initialization(std::string n, Expression *e);

    virtual void Execute();

    virtual ~Initialization()
    {
        delete exp;
    }
};

#endif // INITIALIZATION_H
