#include "condition.h"

#include "terminalexpression.h"
#include "data.h"

void Condition::Execute()
{
    bool result = static_cast<TerminalExpression*>(exp->evaluate())->
            getData()->CastToBoolean();
    if(result)
        positive->Execute();
    else if(negative != nullptr)
    {
        negative->Execute();
    }
}

Condition::~Condition()
{
    delete exp;
    delete positive;
    if(negative != nullptr)
        delete negative;
}
