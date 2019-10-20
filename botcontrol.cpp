#include "botcontrol.h"

#include "databank.h"
#include <SFML/Graphics.hpp>

BotControl::BotControl(World::Action a) : action(a) {}

void BotControl::Execute()
{
    world->actionSlot = action;
    world->used = false;
    world->mutex.unlock();
    do
    {
        sf::sleep(sf::microseconds(10));
        world->mutex.lock();
        if(world->used)
            break;
        world->mutex.unlock();
    } while(true);
    for(unsigned i = 0; i < world->events.size(); ++i)
        bank.raiseEvent(world->events[i]);
}

World *BotControl::world;
