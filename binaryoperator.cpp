#include "binaryoperator.h"

BinaryOperator::BinaryOperator(Expression *l, Expression *r) : left(l), right(r) {}

BinaryOperator::~BinaryOperator()
{
    delete left;
    delete right;
}
