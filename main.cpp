// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Game.hpp"

int main()
{
    Game game(sf::VideoMode(1920, 1080), sf::String("Game"));
    game.run();
}