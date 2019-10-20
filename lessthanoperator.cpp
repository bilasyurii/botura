#include "lessthanoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

LessThanOperator::LessThanOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *LessThanOperator::evaluate()
{
    Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    return new Literal(new Data("", Less(l, r)));
}
