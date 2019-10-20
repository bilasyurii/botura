#include "andoperator.h"

#include "literal.h"
#include "data.h"

AndOperator::AndOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *AndOperator::evaluate()
{
    bool l = static_cast<TerminalExpression*>(left->evaluate())->
            getData()->CastToBoolean();
    if(!l)
        return new Literal(new Data("", false));
    bool r = static_cast<TerminalExpression*>(right->evaluate())->
            getData()->CastToBoolean();
    return new Literal(new Data("", r));
}
