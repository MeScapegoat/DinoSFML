#include "Game.h"

int main()
{
    Game game(sf::VideoMode(640, 480), sf::String("Game"));
    game.run();
}