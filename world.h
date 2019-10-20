#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "bot.h"

class Tile;

class World
{
private:
    void release();
public:
    enum Action
    {
        STAND,
        MOVE,
        TURN_LEFT,
        TURN_RIGHT,
        JUMP,
        END
    };
    Action actionSlot;
    sf::Mutex mutex;
    bool used;
    unsigned width, length, height;
    Tile ****tilesArray;
    bool wallAhead, onEdge;
    Bot bot;
    std::vector<std::string> events;
    sf::Clock timer;
    float delta;

    World();
    void moveForward();
    void checkState();
    void updateDelta();
    bool update();
    void loadFromFile(std::string path);
    virtual ~World();
};

#endif // WORLD_H
