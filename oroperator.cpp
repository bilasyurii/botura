#include "oroperator.h"

#include "literal.h"
#include "data.h"

OrOperator::OrOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *OrOperator::evaluate()
{
    bool l = static_cast<TerminalExpression*>(left->evaluate())->
            getData()->CastToBoolean();
    if(l)
        return new Literal(new Data("", true));
    bool r = static_cast<TerminalExpression*>(right->evaluate())->
            getData()->CastToBoolean();
    return new Literal(new Data("", r));
}
