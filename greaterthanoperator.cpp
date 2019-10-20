#include "greaterthanoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

GreaterThanOperator::GreaterThanOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *GreaterThanOperator::evaluate()
{
    Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    return new Literal(new Data("", Greater(l, r)));
}
