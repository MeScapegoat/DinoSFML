#include "Game.h"

int main()
{
    Game game(sf::VideoMode(1920, 1080), sf::String("Game"));
    game.run();
}