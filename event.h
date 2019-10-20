#ifndef EVENT_H
#define EVENT_H

#include "statement.h"
#include <vector>

class Function;

class Event : public Statement
{
public:
    std::vector<Function*> listeners;

    virtual void Execute();

    virtual ~Event();
};

#endif // EVENT_H
