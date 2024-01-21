#pragma once

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

// мое добро
#include "Background.hpp"
#include "Enemies.hpp"
#include "Player.hpp"
#include "Scoreboard.hpp"
#include "InfoText.hpp"

class Game
{
public:
    Game(sf::VideoMode mode, const sf::String &title, uint32_t style = sf::Style::Default);
    ~Game() = default;

public:
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;

public:
    void run();
    void update();
    void render();
    void restart();

private:
    sf::RenderWindow window;

    InfoText gameOverText;
    InfoText pausedText;
    Scoreboard scoreboard;

    Background background;
    Enemies enemies;
    Player player;

    sf::Font font;

    float elapsedTime;

    float worldVelocity;
    float worldVelocityStep;
    float maxWorldVelocity;

    bool isPaused;
    bool isGameOver;

    sf::Event event{};
    sf::Clock clock;
};