#include "statementlist.h"

void StatementList::Execute()
{
    for(Statement *s : statements)
        s->Execute();
}

StatementList::~StatementList()
{
    for(Statement *s : statements)
        delete s;
}
