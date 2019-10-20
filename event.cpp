#include "event.h"
#include "function.h"

void Event::Execute()
{
    for(unsigned i = 0; i < listeners.size(); ++i)
        listeners[i]->Execute();
}

Event::~Event()
{
    for(unsigned i = 0; i < listeners.size(); ++i)
        delete listeners[i];
}
