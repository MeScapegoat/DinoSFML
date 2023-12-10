#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <deque>

#include "Background.h"

class Game
{
public:
    Game(sf::VideoMode mode, const sf::String &title, uint32_t style = sf::Style::Default);
    ~Game();

public:
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;

public:
    void processEvent();
    void update();
    void render();
    void run();

private:
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Event event;
    Background background;
    sf::Vector2f velocity;
    std::vector<Model> groundEnemies;
    std::vector<Model> flyingEnemies;
    Model player;
};