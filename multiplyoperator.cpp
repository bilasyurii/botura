#include "multiplyoperator.h"

#include "literal.h"
#include "data.h"
#include "stringoperations.h"

MultiplyOperator::MultiplyOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *MultiplyOperator::evaluate()
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
            res = new Literal(new Data("", *(l->getBoolean()) &&
                                           *(r->getBoolean())));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) *
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                           BooleanToInt(*(l->getBoolean())))));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) *
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
            res = new Literal(new Data("", *(l->getFloat()) *
                                           BooleanToInt(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", *(l->getFloat()) *
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                           FloatToInt(*(l->getFloat())))));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getFloat()) *
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
            res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                           BooleanToInt(*(r->getBoolean())))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                           FloatToInt(*(r->getFloat())))));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", findStr(*(l->getString()),
                                           *(r->getString()))));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                           *(r->getInt()))));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::INTEGER:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data("", *(l->getInt()) *
                                           BooleanToInt(*(r->getBoolean()))));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", *(l->getInt()) *
                                           *(r->getFloat())));
            break;
        case VarType::STRING:
            res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                           *(l->getInt()))));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getInt()) *
                                           *(r->getInt())));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::PNULL:
        res = new Literal(new Data(""));
        break;
    }
    return res;
}
