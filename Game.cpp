// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>

#include "Game.hpp"

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style),
      gameOverText(&window),
      pausedText(&window),
      scoreboard(&window),
      background(&window),
      player(&window),
      enemies(&window, &player),
      isGameOver(false)
{
    const auto &size = window.getSize();

    // Расположение
    scoreboard.setPosition(0, size.y);
    pausedText.setPosition(window.getSize().x / 2, window.getSize().y * 0.4f);
    gameOverText.setPosition(window.getSize().x / 2, window.getSize().y * 0.4f);

    // Внешний вид
    background.loadCloudTexture("../Textures/cloud.png");     // Текстура облака
    background.loadTreeTexture("../Textures/tree.png");       // Текстура дерева
    enemies.loadFlyingEnemiesTexture("../Textures/bat.png");  // текстуры летучей мыши
    enemies.loadGroundEnemiesTexture("../Textures/worm.png"); // текстуры червяка
    player.loadTexture("../Textures/player.png");             // текстура игрока

    background.setCloudsAmount(3);                                         // кол-во облаков
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f)); // размер облаков
    background.setTreesAmount(11);                                         // кол-во деревьев
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));   // размер деревьев

    font.loadFromFile("../LOST_LATE.ttf");

    scoreboard.setFont(font);
    scoreboard.setFillColor(sf::Color::Red);

    pausedText.setGeneralFont(font);
    pausedText.setTitleText("Game is Paused!");
    pausedText.setContentText("ESC - pause/continue\n"
                              "arrow up/W - jump\n"
                              "arrow down/S - slide");
    pausedText.title.setFillColor(sf::Color::Red);
    pausedText.content.setFillColor(sf::Color::Red);
    // pausedText.content.setOutlineColor(sf::Color::Cyan);
    // pausedText.content.setOutlineThickness(1.f);

    gameOverText.setGeneralFont(font);
    gameOverText.setTitleText("Game over!");
    gameOverText.setContentText("Press ESC to continue");
    gameOverText.title.setFillColor(sf::Color::Red);
    gameOverText.content.setFillColor(sf::Color::Red);

    // Геймплейное
    player.jumpHeight = size.y * 0.5f;
    isPaused = true;
    pausedText.isActive = true;

    restart();
}

void Game::restart()
{
    const auto &size = window.getSize();
    background.init();

    enemies.setGroundHeight(background.getGround());
    player.groundLevel = background.getGround();
    scoreboard.setCharacterSize(size.y - background.road.getPosition().y);
    scoreboard.setOrigin(0, scoreboard.getCharacterSize());

    enemies.init();
    worldVelocity = 200;
    maxWorldVelocity = worldVelocity * 5;
    worldVelocityStep = (maxWorldVelocity - worldVelocity) / 100;
    elapsedTime = 0;

    player.model.sprite.setPosition(size.x * 0.15f + player.model.getSize().x / 2,
                                    background.getGround() - player.model.getSize().y / 2);
    player.jumpVelocity = size.y * 0.001f;
    player.maxJumpVelocity = player.jumpVelocity * 10;
    player.jumpVelocityStep = (player.maxJumpVelocity - player.jumpVelocity) / 100;

    enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
    scoreboard.setScore(0);
}

void Game::render()
{
    if (!window.isOpen())
        return;

    window.clear(sf::Color::Black);

    background.draw();
    scoreboard.draw();
    enemies.draw();
    player.model.draw();

    pausedText.draw();
    gameOverText.draw();

    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;
    elapsedTime = clock.restart().asSeconds();
    //
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                if (isGameOver)
                {
                    restart();
                    isGameOver = !isGameOver;
                    gameOverText.isActive = !gameOverText.isActive;
                    break;
                }
                isPaused = !isPaused;
                pausedText.isActive = !pausedText.isActive;
                break;
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                player.jump();
                break;

            default:
                break;
            } // switch event.key.code

        default:
            break;
        } // switch event.type
    }

    if (isPaused or isGameOver)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.setSliding(true);
    else
        player.setSliding(false);
    //

    if (enemies.checkCrash())
    {
        // isGameOver = true;
        // gameOverText.toShow = true;
        // return;
    }

    if (enemies.checkOvercome())
        scoreboard.increaseScore(1);

    if (enemies.spawn(elapsedTime))
    {
        enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldVelocityStep;
            player.jumpVelocity += player.jumpVelocityStep;
        }
    }
    enemies.updateAnimations(elapsedTime);

    auto speed = worldVelocity * elapsedTime * -1.f;
    background.move(sf::Vector2f(speed, 0));
    enemies.move(sf::Vector2f(speed, 0));
    player.move(elapsedTime);
}

void Game::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}