#include "initialization.h"

#include "terminalexpression.h"
#include "data.h"
#include "databank.h"

Initialization::Initialization(std::string n, Expression *e) : Declaration(n), exp(e) {}

void Initialization::Execute()
{
    Declaration::Execute();
    TerminalExpression *result = static_cast<TerminalExpression*>(exp->evaluate());
    bank.get(name)->copyFrom(result->getData());
}
