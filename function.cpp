#include "function.h"
#include "statementlist.h"

Function::Function(std::string n, StatementList *s) : name(n), statements(s) {}

void Function::Execute()
{
    statements->Execute();
}
