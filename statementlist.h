#ifndef STATEMENTLIST_H
#define STATEMENTLIST_H

#include "statement.h"
#include <vector>

class StatementList : public Statement
{
public:
    std::vector<Statement*> statements;

    virtual void Execute();

    virtual ~StatementList();
};

#endif // STATEMENTLIST_H
