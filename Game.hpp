#pragma once

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/Music.hpp>

// мое добро
#include "Background.hpp"
#include "Enemies.hpp"
#include "Player.hpp"
#include "Scoreboard.hpp"
#include "InfoText.hpp"

class Game
{
public:
    Game(sf::VideoMode mode, const sf::String &title, uint32_t style = sf::Style::Fullscreen);
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

    InfoText gameOverText; // Уведомление о конце игры
    InfoText pausedText;   // Уведомление о паузе
    Scoreboard scoreboard; // счетчик очков

    Background background; // фон: деревья, облака, дорога
    Enemies enemies;       // враги
    Player player;         // игрок

    sf::Font font;

    float elapsedTime; // время прошедшее с последней итерации игры

    float worldVelocity;     // Скорость мира (окружения)
    float worldAcceleration; // Ускорение мира
    float maxWorldVelocity;  // максимальная скорость мира

    bool isPaused;
    bool isGameOver;

    sf::Music soundtrack;
    sf::Event event;
    sf::Clock clock;
};