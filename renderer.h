#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
class World;

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

    Renderer(World &W);
    void loop();
    sf::Vector2i calcCoords(unsigned x, unsigned y, unsigned z);
    void drawTile(unsigned x, unsigned y, unsigned z);
    void draw();
};



#endif // RENDERER_H
