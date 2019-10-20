#include "notequalsoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

NotEqualsOperator::NotEqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *NotEqualsOperator::evaluate()
{
    Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    return new Literal(new Data("", !Equals(l, r)));
}
