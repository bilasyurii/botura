#include "raise.h"

#include "databank.h"

Raise::Raise(std::string e) : event(e) {}

void Raise::Execute()
{
    bank.raiseEvent(event);
}
