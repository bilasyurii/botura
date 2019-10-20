#include "modulooperator.h"

#include <math.h>
#include "literal.h"
#include "data.h"
#include "stringoperations.h"

ModuloOperator::ModuloOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

Expression *ModuloOperator::evaluate()
{
    Data *l, *r;
    l = static_cast<TerminalExpression*>(left->evaluate())->getData();
    r = static_cast<TerminalExpression*>(right->evaluate())->getData();
    Literal *res = nullptr;
    switch(l->type)
    {
    case VarType::BOOLEAN:
        res = new Literal(new Data(""));
        break;
    case VarType::FLOAT:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data(""));
            break;
        case VarType::FLOAT:
            res = new Literal(new Data("", (float) fmod(*(l->getFloat()),
                                                        *(r->getFloat()))));
            break;
        case VarType::STRING:
            res = new Literal(new Data(""));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", (float) fmod(*(l->getFloat()),
                                                        *(r->getInt()))));
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        break;
    case VarType::STRING:
        res = new Literal(new Data(""));
        break;
    case VarType::INTEGER:
        switch(r->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data(""));
            break;
        case VarType::FLOAT:
            if(*(r->getFloat()) == 0.0f)
                res = new Literal(new Data(""));
            else
                res = new Literal(new Data("", (float) fmod(*(l->getInt()),
                                                            *(r->getFloat()))));
            break;
        case VarType::STRING:
            res = new Literal(new Data(""));
            break;
        case VarType::INTEGER:
            res = new Literal(new Data("", *(l->getInt()) %
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
