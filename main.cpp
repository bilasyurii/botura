#include <iostream>
#include <string>
#include "parser.h"
#include <SFML/Graphics.hpp>
#include "world.h"
#include "renderer.h"
#include "botcontrol.h"

int main()
{
    std::string code = Parser::readFromFile("in.txt");
    sf::Mutex mutex;
    World w;
    Renderer r(w);
    Parser parser(w);
    BotControl::world = &w;
    try
    {
        w.loadFromFile(parser.analyse(code));
    }
    catch(...)
    {
        std::cout << "\nThere were errors during parsing.\n";
        return 0;
    }
    sf::Thread renderThread(&Renderer::loop, &r);
    renderThread.launch();
    sf::Thread parserThread(&Parser::Execute, &parser);
    parserThread.launch();
    parserThread.wait();
    renderThread.wait();
    return 0;
}
