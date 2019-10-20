#include "world.h"
#include "tile.h"
#include "bot.h"
#include <fstream>

void World::release()
{
    if(tilesArray == nullptr)
        return;
    for(unsigned z = 0; z < height; ++z)
    {
        for(unsigned y = 0; y < length; ++y)
        {
            for(unsigned x = 0; x < width; ++x)
                if(tilesArray[z][y][x] != nullptr)
                    delete tilesArray[z][y][x];
            delete tilesArray[z][y];
        }
        delete tilesArray[z];
    }
}

World::World() : actionSlot(END), used(false), tilesArray(nullptr),
          wallAhead(false), onEdge(false) {}

void World::moveForward()
{
    switch(bot.dir)
    {
    case Bot::LB:
        ++bot.pos.y;
        break;
    case Bot::RB:
        ++bot.pos.x;
        break;
    case Bot::LT:
        --bot.pos.x;
        break;
    case Bot::RT:
        --bot.pos.y;
        break;
    }
}

void World::checkState()
{
    sf::Vector3i backup = bot.pos;
    moveForward();
    if(bot.pos.x >= 0 && bot.pos.y >= 0 && bot.pos.z >= 0 &&
       bot.pos.x < width && bot.pos.y < length && bot.pos.z < height)
    {
        wallAhead = tilesArray[bot.pos.z + 1][bot.pos.y][bot.pos.x] != nullptr;
        onEdge = tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] == nullptr;
    }
    bot.pos = backup;
}

void World::updateDelta()
{
    delta = timer.restart().asSeconds();
}

bool World::update()
{
    events = std::vector<std::string>();
    wallAhead = false;
    onEdge = false;
    bot.prev = bot.pos;
    switch(actionSlot)
    {
    case STAND:
        break;
    case MOVE:
        {
            checkState();
            if(!wallAhead && !onEdge)
                moveForward();
            checkState();
        }
        break;
    case TURN_LEFT:
        switch(bot.dir)
        {
        case Bot::LB:
            bot.dir = Bot::RB;
            break;
        case Bot::RB:
            bot.dir = Bot::RT;
            break;
        case Bot::LT:
            bot.dir = Bot::LB;
            break;
        case Bot::RT:
            bot.dir = Bot::LT;
            break;
        }
        break;
    case TURN_RIGHT:
        switch(bot.dir)
        {
        case Bot::LB:
            bot.dir = Bot::LT;
            break;
        case Bot::RB:
            bot.dir = Bot::LB;
            break;
        case Bot::LT:
            bot.dir = Bot::RT;
            break;
        case Bot::RT:
            bot.dir = Bot::RB;
            break;
        }
        break;
    case JUMP:
        moveForward();
        ++bot.pos.z;
        if(tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] == nullptr)
        {
            --bot.pos.z;
            if(tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] != nullptr)
                bot.pos = bot.prev;
            else
            {
                while(bot.pos.z >= 0)
                {
                    if(tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] != nullptr)
                        break;
                    --bot.pos.z;
                }
                if(tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] == nullptr)
                    bot.pos = bot.prev;
            }
        }
        else if(tilesArray[bot.pos.z + 1][bot.pos.y][bot.pos.x] != nullptr)
            bot.pos = bot.prev;
        break;
    case END:
        return false;
    }
    checkState();
    if(wallAhead)
        events.push_back("WALL_AHEAD");
    else if(onEdge)
        events.push_back("ON_EDGE");
    return true;
}

void World::loadFromFile(std::string path)
{
    std::ifstream fin;
    fin.open(path);
    std::string method, type, axis, dir;
    unsigned x, y, z, axisCount;
    bool axises[3];
    unsigned axisFillSizes[3];
    fin >> width;
    fin >> length;
    fin >> height;
    release();
    tilesArray = new Tile***[height];
    for(unsigned z = 0; z < height; ++z)
    {
        tilesArray[z] = new Tile**[length];
        for(unsigned y = 0; y < length; ++y)
        {
            tilesArray[z][y] = new Tile*[width];
            for(unsigned x = 0; x < width; ++x)
                tilesArray[z][y][x] = nullptr;
        }
    }

    while(fin >> method)
    {
        if(method == "single")
        {
            fin >> type;
            if(type == "tile")
            {
                fin >> x;
                fin >> y;
                fin >> z;
                tilesArray[z][y][x] = new Tile(x, y, z);
            }
            else if(type == "bot")
            {
                fin >> bot.pos.x;
                fin >> bot.pos.y;
                fin >> bot.pos.z;
                fin >> dir;
                if(dir == "lb")
                    bot.dir = Bot::LB;
                else if(dir == "rb")
                    bot.dir = Bot::RB;
                else if(dir == "lt")
                    bot.dir = Bot::LT;
                else if(dir == "rt")
                    bot.dir = Bot::RT;
                bot.prev = bot.pos;
            }
        }
        else if(method == "many")
        {
            for(unsigned i = 0; i < 3; ++i)
                axises[i] = false;
            fin >> axisCount;
            for(unsigned i = 0; i < axisCount; ++i)
            {
                fin >> axis;
                if(axis == "x")
                    axises[0] = true;
                else if(axis == "y")
                    axises[1] = true;
                else if(axis == "z")
                    axises[2] = true;
            }
            for(unsigned i = 0; i < 3; ++i)
            {
                if(axises[i])
                    fin >> axisFillSizes[i];
                else
                    axisFillSizes[i] = 1;
            }
            fin >> type;
            if(type == "tile")
            {
                fin >> x;
                fin >> y;
                fin >> z;
                for(unsigned i = 0; i < axisFillSizes[0]; ++i)
                    for(unsigned j = 0; j < axisFillSizes[1]; ++j)
                        for(unsigned k = 0; k < axisFillSizes[2]; ++k)
                            tilesArray[z + k][y + j][x + i] =
                                new Tile(x + i, y + j, z + k);
            }
        }
    }
    fin.close();
}

World::~World()
{
    release();
}
