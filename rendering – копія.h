#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <fstream>
#include <algorithm>
#include "helper.h"

class Tile
{
public:
    unsigned x, y, z;

    Tile(unsigned X, unsigned Y, unsigned Z) : x(X), y(Y), z(Z) {}

    Tile() : x(0), y(0), z(0) {}
};

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

class World
{
private:
    void release()
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

    World() : actionSlot(END), used(false), tilesArray(nullptr),
              wallAhead(false), onEdge(false) {}

    void moveForward()
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

    void checkState()
    {
        sf::Vector3i backup = bot.pos;
        moveForward();
        wallAhead = tilesArray[bot.pos.z + 1][bot.pos.y][bot.pos.x] != nullptr;
        onEdge = tilesArray[bot.pos.z][bot.pos.y][bot.pos.x] == nullptr;
        bot.pos = backup;
    }

    void updateDelta()
    {
        delta = timer.restart().asSeconds();
    }

    bool update()
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

    void loadFromFile(std::string path)
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

    virtual ~World()
    {
        release();
    }
};

class Renderer
{
public:
    static const unsigned WIDTH = 1000, HEIGHT = 600;
    static const unsigned XTORIGHT = 36, YTORIGHT = 12,
                          XTOLEFT = 33, YTOLEFT = 11,
                          YTOTOP = 10,
                          PIVOTX = 400, PIVOTY = 100,
                          YBOTTOP = 34, XBOTRIGHT = 12;
    static const float ANIM_TIME;
    World &w;
    sf::RenderWindow window;
    sf::Texture tex;
    sf::Sprite spr;
    float currAnimTime;

    Renderer(World &W) : w(W), window(sf::VideoMode(WIDTH, HEIGHT), "Botura"),
                        currAnimTime(0.0f)
    {
        tex.loadFromFile("res/spritelist.png");
        spr.setTexture(tex);
        window.setActive(false);
    }

    void loop()
    {
        window.setActive(true);
        w.mutex.lock();
        if(!w.update())
        {
            window.clear();
            draw();
            window.display();
            window.close();
        }
        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
                if(event.type == sf::Event::Closed)
                    window.close();
            window.clear();
            draw();
            window.display();
            w.updateDelta();
            currAnimTime += 2.0f * w.delta;
            if(currAnimTime >= ANIM_TIME)
            {
                currAnimTime = 0.0f;
                w.actionSlot = World::STAND;
                w.mutex.unlock();
                sf::sleep(sf::microseconds(1));
                w.mutex.lock();
                w.used = true;
                if(!w.update())
                    window.close();
            }
        }
        sf::sleep(sf::seconds(1));
        w.mutex.unlock();
    }

    sf::Vector2i calcCoords(unsigned x, unsigned y, unsigned z)
    {
        return sf::Vector2i(PIVOTX + x * XTORIGHT - y * XTOLEFT,
                            PIVOTY + x * YTORIGHT + y * YTOLEFT - z * YTOTOP);
    }

    void drawTile(unsigned x, unsigned y, unsigned z)
    {
        Tile *t = w.tilesArray[z][y][x];
        if(t == nullptr)
            return;
        sf::Vector2i pos = calcCoords(t->x, t->y, t->z);
        spr.setTextureRect(sf::IntRect(0, 0, 70, 34));
        spr.setPosition(pos.x, pos.y);
        window.draw(spr);
        if(t->x == w.bot.pos.x && t->y == w.bot.pos.y && t->z == w.bot.pos.z)
        {
            switch(w.actionSlot)
            {
            case World::END:
            case World::STAND:
            case World::TURN_LEFT:
            case World::TURN_RIGHT:
                spr.setPosition(pos.x + XBOTRIGHT, pos.y - YBOTTOP);
                break;
            case World::JUMP:
            case World::MOVE:
                {
                    sf::Vector2i prev = calcCoords(w.bot.prev.x, w.bot.prev.y, w.bot.prev.z);
                    sf::Vector2i diff = pos - prev;
                    spr.setPosition(prev.x + diff.x * (currAnimTime / ANIM_TIME) + XBOTRIGHT,
                                    prev.y + diff.y * (currAnimTime / ANIM_TIME) - YBOTTOP);
                }
                break;
            }
            switch(w.bot.dir)
            {
            case Bot::LB:
                spr.setTextureRect(sf::IntRect(50, 34, -50, 50));
                break;
            case Bot::RB:
                spr.setTextureRect(sf::IntRect(0, 34, 50, 50));
                break;
            case Bot::LT:
                spr.setTextureRect(sf::IntRect(100, 34, -50, 50));
                break;
            case Bot::RT:
                spr.setTextureRect(sf::IntRect(50, 34, 50, 50));
                break;
            }
            window.draw(spr);
        }
    }

    void draw()
    {
        for(unsigned y = 0; y < w.length; ++y)
            for(unsigned x = 0; x < w.width; ++x)
                for(unsigned z = 0; z < w.height; ++z)
                    drawTile(x, y, z);
    }
};

const float Renderer::ANIM_TIME = 1.0f;
