#ifndef SCOPECONTROL_H
#define SCOPECONTROL_H

#include "statement.h"

class ScopeControl : public Statement
{
public:
    enum ScopeAction
    {
        CREATE,
        DELETE
    };
    ScopeAction action;
    ScopeControl(ScopeAction a);

    virtual void Execute();

    virtual ~ScopeControl() {}
};

#endif // SCOPECONTROL_H
