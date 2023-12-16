#include "Game.h"

int main()
{
    Game game(sf::VideoMode(1500, 1000), sf::String("Game"));
    game.run();
}