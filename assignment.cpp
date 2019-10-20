#include "assignment.h"

#include "terminalexpression.h"
#include "data.h"
#include "variable.h"
#include "databank.h"
#include <string>

Assignment::Assignment(Expression *l, Expression *r) : left(l), right(r) {}

void Assignment::Execute()
{
    std::string name = static_cast<Variable*>(left)->getData()->name;
    TerminalExpression *result = static_cast<TerminalExpression*>(right->evaluate());
    bank.get(name)->copyFrom(result->getData());
}

Assignment::~Assignment()
{
    delete left;
    delete right;
}
