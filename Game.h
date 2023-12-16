#pragma once
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Background.h"
#include "Enemies.h"
#include "Player.h"
#include "Randomizer.h"

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
    void run();
    void processEvent();
    void update();
    void render();

private:
    sf::RenderWindow window;

    float elapsedTime;
    float timePassed;
    float minSpawnInterval;
    float spawnInterval;

    Background background;
    Player player;
    Enemies enemies;

    float worldVelocity; // x
    float worldVelocityStep;
    float maxWorldVelocity;
    float playerVelocity; // y
    float playerVelocityStep;

    sf::Event event;
    Randomizer random;
    sf::Clock clock;
};