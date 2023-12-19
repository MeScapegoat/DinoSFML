#include "Game.hpp"

int main()
{
    Game game(sf::VideoMode(1500, 1000), sf::String("Game"));
    game.run();
}