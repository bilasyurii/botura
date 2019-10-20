#include "scopecontrol.h"

#include "databank.h"

ScopeControl::ScopeControl(ScopeAction a) : action(a) {}

void ScopeControl::Execute()
{
    switch(action)
    {
    case CREATE:
        bank.newScope();
        break;
    case DELETE:
        bank.deleteScope();
        break;
    }
}
