#include "logicalnot.h"

#include "data.h"
#include "literal.h"

LogicalNot::LogicalNot(Expression *e) : UnaryOperator(e) {}

Expression *LogicalNot::evaluate()
{
    Data *e = static_cast<TerminalExpression*>(expr->evaluate())->getData();
    switch(e->type)
    {
    case VarType::BOOLEAN:
        return new Literal(new Data("", !(*(e->getBoolean()))));
    case VarType::FLOAT:
        return new Literal(new Data("", *(e->getFloat()) == 0.0f));
    case VarType::INTEGER:
        return new Literal(new Data("", *(e->getInt()) == 0));
    case VarType::PNULL:
        return new Literal(new Data(""));
    case VarType::STRING:
        return new Literal(new Data("", *(e->getString()) == ""));
    }
    return nullptr;
}
