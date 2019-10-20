#ifndef BOTCONTROL_H
#define BOTCONTROL_H

#include "statement.h"
#include "world.h"

class BotControl : public Statement
{
public:
    static World *world;
    World::Action action;

    BotControl(World::Action a);

    virtual void Execute();
    virtual ~BotControl() {}
};

#endif // BOTCONTROL_H
