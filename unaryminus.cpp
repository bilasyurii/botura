#include "unaryminus.h"
#include "data.h"
#include "literal.h"

UnaryMinus::UnaryMinus(Expression *e) : UnaryOperator(e) {}

Expression *UnaryMinus::evaluate()
{
    Data *e = static_cast<TerminalExpression*>(expr->evaluate())->getData();
    switch(e->type)
    {
    case VarType::BOOLEAN:
        return new Literal(new Data(""));
    case VarType::FLOAT:
        return new Literal(new Data("", -*(e->getFloat())));
    case VarType::INTEGER:
        return new Literal(new Data("", -*(e->getInt())));
    case VarType::PNULL:
        return new Literal(new Data(""));
    case VarType::STRING:
        return new Literal(new Data(""));
    }
    return nullptr;
}
