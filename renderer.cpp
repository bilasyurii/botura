#include "renderer.h"
#include "tile.h"
#include "world.h"

Renderer::Renderer(World &W) : w(W), window(sf::VideoMode(WIDTH, HEIGHT), "Botura"),
                    currAnimTime(0.0f)
{
    tex.loadFromFile("res/spritelist.png");
    spr.setTexture(tex);
    window.setActive(false);
}

void Renderer::loop()
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

sf::Vector2i Renderer::calcCoords(unsigned x, unsigned y, unsigned z)
{
    return sf::Vector2i(PIVOTX + x * XTORIGHT - y * XTOLEFT,
                        PIVOTY + x * YTORIGHT + y * YTOLEFT - z * YTOTOP);
}

void Renderer::drawTile(unsigned x, unsigned y, unsigned z)
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

void Renderer::draw()
{
    for(unsigned y = 0; y < w.length; ++y)
        for(unsigned x = 0; x < w.width; ++x)
            for(unsigned z = 0; z < w.height; ++z)
                drawTile(x, y, z);
}

const float Renderer::ANIM_TIME = 1.0f;
