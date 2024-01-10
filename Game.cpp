// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "Game.hpp"

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style),
      gameOverText(window.getSize()),
      pausedText(window.getSize()),
      background(window.getSize()),
      player("../assets/proto.png"),
      enemies(window.getSize())
{
    const auto &size = window.getSize();

    player.setJumpHeight(size.y * 0.5f);
    player.setSize(size.x * 0.06f, size.y * 0.2f);

    background.setRoadSize(sf::Vector2f(size.x, size.y * 0.05f));
    background.setGroundHeight(size.y * 0.9f);

    background.setCloudsAmount(3);
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f));

    background.setTreesAmount(11);
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));

    background.loadCloudTexture("../assets/cloud.png");
    background.loadTreeTexture("../assets/tree.png");

    enemies.setPlayerSize(player.getSize());
    enemies.loadFlyingEnemiesTextures(std::vector<sf::String>{"../assets/batup.png", "../assets/batdown.png"});
    enemies.loadGroundEnemiesTextures(std::vector<sf::String>{"../assets/wormup.png", "../assets/wormdown.png"});

    enemies.setGroundHeight(background.getGroundHeight());

    font.loadFromFile("../LOST_LATE.ttf");

    scoreboard.setFont(font);
    scoreboard.setPosition(0, size.y);
    scoreboard.setCharacterSize(size.y - background.getGroundHeight() - background.getRoadSize().y / 2);
    scoreboard.setOrigin(0, scoreboard.getCharacterSize());

    pausedText.setFont(font);
    pausedText.setTitleText("Game is Paused!");
    pausedText.setInfoText("ESC - pause/continue\narrow up/W - jump\narrow down/S - slide");
    pausedText.setTextColor(sf::Color::Red);

    gameOverText.setFont(font);
    gameOverText.setTitleText("Game over!");
    gameOverText.setInfoText("Press ESC to continue");
    gameOverText.setTextColor(sf::Color::Red);

    isPaused = true;
    pausedText.toShow = true;

    restart();
}

void Game::restart()
{
    const auto &size = window.getSize();
    background.init();
    enemies.init();
    worldVelocity = 200;
    maxWorldVelocity = worldVelocity * 5;
    worldVelocityStep = (maxWorldVelocity - worldVelocity) / 100;
    elapsedTime = 0;

    player.setPosition(size.x * 0.15f + player.getSize().x / 2,
                       background.getGroundHeight() - player.getSize().y / 2);
    player.setJumpVelocity(size.y * 0.001f * -1);
    player.setJumpVelocityStep(player.getJumpVelocity() / 100);
    enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
    scoreboard.setScore(0);
}

void Game::render()
{
    if (!window.isOpen())
        return;

    window.clear(sf::Color::Black);

    background.draw(window);
    scoreboard.draw(window);
    enemies.draw(window);
    player.draw(window);

    if (pausedText.toShow)
        pausedText.draw(window);
    if (gameOverText.toShow)
        gameOverText.draw(window);

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
                    gameOverText.toShow = !gameOverText.toShow;
                    break;
                }
                isPaused = !isPaused;
                pausedText.toShow = !pausedText.toShow;
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
    {
        if (!player.getCurrentJumpVelocity())
        {
            player.setScale(2.f, 0.5f);
            player.setPosition(player.getPosition().x, background.getGroundHeight() - player.getSize().y / 2);
        }
    }
    else
    {
        if (!player.getCurrentJumpVelocity())
        {
            player.setScale(1.f, 1.f);
            player.setPosition(player.getPosition().x, background.getGroundHeight() - player.getSize().y / 2);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (player.getCurrentJumpVelocity() > 0)
            player.setCurrentJumpVelocity(-1 * player.getJumpVelocity());
        else
            player.setCurrentJumpVelocity(player.getJumpVelocity());
    }
    //

    if (enemies.checkCrash(player))
    {
        // isGameOver = true;
        // gameOverText.toShow = true;
        // return;
    }

    if (enemies.checkOvercome(player))
        scoreboard.setScore(scoreboard.getScore() + 1);

    if (enemies.spawn(elapsedTime))
    {
        enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldVelocityStep;
            player.setJumpVelocity(player.getJumpVelocity() + player.getJumpVelocityStep());
        }
    }
    enemies.updateAnimations(elapsedTime, worldVelocity);

    if (player.getCurrentJumpVelocity() < 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 < player.getJumpHeight())
            player.setCurrentJumpVelocity(player.getCurrentJumpVelocity() * -1);
    }
    else if (player.getCurrentJumpVelocity() > 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 > background.getGroundHeight())
            player.setCurrentJumpVelocity(0);
    }

    auto speed = worldVelocity * elapsedTime * -1.f;
    background.move(sf::Vector2f(speed, 0));
    enemies.move(sf::Vector2f(speed, 0));
    player.move(sf::Vector2f(0, player.getCurrentJumpVelocity()));
}

void Game::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

Game::~Game() {}