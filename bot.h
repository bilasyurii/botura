#ifndef BOT_H
#define BOT_H

#include <SFML/Graphics.hpp>

class Bot
{
public:
    sf::Vector3i pos;
    sf::Vector3i prev;
    enum Direction
    {
        LB,
        RB,
        LT,
        RT
    };
    Direction dir;
};

#endif // BOT_H
