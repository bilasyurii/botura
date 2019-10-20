#include "greaterequalsoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

GreaterEqualsOperator::GreaterEqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *GreaterEqualsOperator::evaluate()
{
    Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    return new Literal(new Data("", Greater(l, r) || Equals(l, r)));
}
