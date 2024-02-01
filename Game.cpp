// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>

#include "Game.hpp"

#include <iostream>

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

    font.loadFromFile("../fonts/HERO.ttf");

    scoreboard.setFont(font);

    pausedText.setGeneralFont(font);
    pausedText.setTitleText(L"Игра приостановлена!!");
    pausedText.setContentText(L"ESC - пауза/продолжить\n"
                              L"стрелочка вверх/W - прыжок\n"
                              L"стрелочка вниз/S - скольжение\n"
                              L"Z - выход из игры");
    pausedText.setPosition(size.x / 2, size.y * 0.4f);

    gameOverText.setGeneralFont(font);
    gameOverText.setTitleText(L"Конец игры!");
    gameOverText.setContentText(L"Нажми ESC чтобы продолжить\n"
                                L"Нажми Z чтобы выйти");
    gameOverText.setPosition(size.x / 2, size.y * 0.4f);

    isPaused = true;
    pausedText.isActive = true;

    soundtrack.openFromFile("../Sound/Toys - Hunter Milo.ogg"); // Говорят что это Copyright free
    soundtrack.setLoopPoints({sf::seconds(1.7f), sf::seconds(6.f)});
    soundtrack.setPlayingOffset(soundtrack.getLoopPoints().offset);
    soundtrack.setLoop(true);
    soundtrack.setVolume(30);

    enemies.setGroundHeight(background.getGround());
    player.groundLevel = background.getGround();
    scoreboard.setCharacterSize(size.y - background.getGround());
    scoreboard.setOrigin(0, scoreboard.getCharacterSize());
    scoreboard.setPosition(0, size.y * 0.99f);

    maxWorldVelocity = worldVelocity * 5;
    worldVelocity = 200;
    worldAcceleration = (maxWorldVelocity - worldVelocity) / 100;

    player.jumpVelocity = worldVelocity / 1.5f;
    player.maxJumpVelocity = maxWorldVelocity / 1.5f;
    player.jumpAcceleration = (player.maxJumpVelocity - player.jumpVelocity) / 100;

    restart();

    player.jumpHeight = player.groundLevel - enemies.getWormSize().y * 2;
}

void Game::restart()
{
    background.restart();
    enemies.restart();

    worldVelocity = 200;
    elapsedTime = 0;

    const auto &size = window.getSize();
    player.model.sprite.setPosition(size.x * 0.15f + player.model.getSize().x / 2,
                                    background.getGround() - player.model.getSize().y / 2);
    player.jumpVelocity = worldVelocity / 1.5f;

    enemies.setMinSpawnInterval(enemies.getBetweenDistance() / worldVelocity);
    scoreboard.setScore(0);
}

void Game::render()
{
    if (!window.isOpen())
        return;

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
                    isGameOver = false;
                    gameOverText.isActive = false;
                    break;
                }
                isPaused = !isPaused;
                pausedText.isActive = !pausedText.isActive;
                break;
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                player.jump();
                break;
            case sf::Keyboard::Z:
                if (isGameOver or isPaused)
                    window.close();
            default:
                break;
            } // switch event.key.code

        default:
            break;
        } // switch event.type
    }

    if (isPaused or isGameOver)
    {
        soundtrack.pause();
        return;
    }
    if (soundtrack.getStatus() != sf::Music::Status::Playing)
        soundtrack.play();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.setSliding(true);
    else
        player.setSliding(false);
    //

    if (enemies.checkCrash())
    {
        isGameOver = true;
        gameOverText.isActive = true;
        return;
    }

    if (enemies.checkOvercome())
        scoreboard.increaseScore(1);

    if (enemies.spawn(elapsedTime))
    {
        enemies.setMinSpawnInterval(enemies.getBetweenDistance() / worldVelocity);
        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldAcceleration;
            player.jumpVelocity += player.jumpAcceleration;
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