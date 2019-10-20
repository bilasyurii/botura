#ifndef MODULOOPERATOR_H
#define MODULOOPERATOR_H

#include "binaryoperator.h"

class ModuloOperator : public BinaryOperator
{
public:
    ModuloOperator(Expression *l, Expression *r);

    virtual Expression *evaluate();

    virtual ~ModuloOperator() {}
};

#endif // MODULOOPERATOR_H
