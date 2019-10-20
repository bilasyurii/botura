#include "print.h"

#include "terminalexpression.h"
#include "data.h"
#include "stringoperations.h"
#include <iostream>

Print::Print(Expression *e) : exp(e) {}

void Print::Execute()
{
    Data *d = static_cast<TerminalExpression*>(exp->evaluate())->getData();
    switch(d->type)
    {
    case VarType::PNULL:
        std::cout << "null";
        break;
    case VarType::INTEGER:
        std::cout << *(d->getInt());
        break;
    case VarType::FLOAT:
        std::cout << *(d->getFloat());
        break;
    case VarType::STRING:
        std::cout << *(d->getString());
        break;
    case VarType::BOOLEAN:
        std::cout << BooleanToString(*(d->getBoolean()));
        break;
    }
}
