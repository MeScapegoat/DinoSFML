#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Background.h"
#include "Enemies.h"

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

public:
private:
    int type = 1;
    sf::Clock clock;
    float elapsedTime;
    float timePassed;
    float spawnInterval;
    sf::RenderWindow window;
    sf::Event event;
    Background background;
    sf::Vector2f velocity;
    Model player;
    Enemies enemies;
};