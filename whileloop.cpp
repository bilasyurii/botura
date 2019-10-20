#include "whileloop.h"

#include "terminalexpression.h"
#include "data.h"

void WhileLoop::Execute()
{
    bool result;
    while(true)
    {
        result = static_cast<TerminalExpression*>(exp->evaluate())->
            getData()->CastToBoolean();
        if(!result)
            return;
        action->Execute();
    }
}

WhileLoop::~WhileLoop()
{
    delete exp;
    delete action;
}
