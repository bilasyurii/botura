#include "plusoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

PlusOperator::PlusOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *PlusOperator::evaluate()
{
    Data *l, *r;
    l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    Literal *res = nullptr;
    switch(l->type)
    {
    case VarType::BOOLEAN:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) +
                                           BooleanToInt(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", BooleanToFloat(*(l->getBoolean())) +
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", BooleanToString(*(l->getBoolean())) +
                                           *(r->getString())));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) +
                                           *(r->getInt())));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::FLOAT:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data("", *(l->getFloat()) +
                                           BooleanToFloat(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", *(l->getFloat()) +
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", FloatToString(*(l->getFloat())) +
                                           *(r->getString())));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getFloat()) +
                                           *(r->getInt())));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::STRING:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data("", *(l->getString()) +
                                           BooleanToString(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", *(l->getString()) +
                                           FloatToString(*(r->getFloat()))));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", *(l->getString()) +
                                           *(r->getString())));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getString()) +
                                           IntToString(*(r->getInt()))));
            break;
        case VarType::PNULL:
            res = new Literal(new Data("", *(l->getString()) +
                                           "null"));
            break;
        }
        break;
    case VarType::INTEGER:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data("", *(l->getInt()) +
                                           BooleanToInt(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", *(l->getInt()) +
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", IntToString(*(l->getInt())) +
                                           *(r->getString())));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getInt()) +
                                           *(r->getInt())));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::PNULL:
        if(r->type == VarType::STRING)
            res = new Literal(new Data("", "null" + *(r->getString())));
        else
            res = new Literal(new Data(""));
        break;
    }
    return res;
}
