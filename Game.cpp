#include <SFML/Window/Event.hpp>

#include <iostream>

#include "Game.hpp"

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style),
      background(window.getSize()),
      player(window.getSize()),
      enemies(window.getSize(), player.getSize()),
      scoreboard("../LOST_LATE.ttf"),
      worldVelocity(200),
      worldVelocityStep(worldVelocity * (9.f / 100)), // 9.f/y, where y is at which spawn count we reach max speed if max speed is 10x base speed
      maxWorldVelocity(worldVelocity * 10),
      playerVelocityStep(window.getSize().y * 0.001f * -1 * (9.f / 100))
{
    auto size = window.getSize();

    background.setRoadSize(sf::Vector2f(size.x, size.y * 0.05f));
    background.setGroundHeight(size.y * 0.9f);

    background.setCloudsAmount(3);
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f));

    background.setTreesAmount(11);
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));
    background.init();

    player.setPosition(size.x * 0.15f + player.getSize().x / 2,
                       background.getGroundHeight() - player.getSize().y / 2);
    player.setFillColor(sf::Color(0, 255, 0));
    player.setJumpHeight(size.y * 0.5f);
    player.setJumpVelocity(size.y * 0.001f * -1);

    minSpawnInterval = std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity;
    spawnInterval = random.getFloat(minSpawnInterval, 2 * minSpawnInterval);

    enemies.setGroundHeight(background.getGroundHeight());
    enemies.spawn(random.getInt(0, 1));

    scoreboard.setPosition(0, window.getSize().y);
    scoreboard.setFillColor(sf::Color::Red);
    scoreboard.setCharacterSize(window.getSize().y - background.getGroundHeight() - background.getRoadSize().y / 2);
    scoreboard.setOrigin(0, scoreboard.getCharacterSize());
}

void Game::processEvent()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        isCrawling = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (playerVelocity > 0)
            playerVelocity = -1 * player.getJumpVelocity();
        else
            playerVelocity = player.getJumpVelocity();
    }

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

            default:
                break;
            }
        default:
            break;
        }
    }
}

void Game::render()
{
    if (!window.isOpen())
        return;

    window.clear(sf::Color::Black);

    background.draw(window);
    player.draw(window);
    enemies.draw(window);
    scoreboard.draw(window);

    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;
    if (enemies.checkCrash(player))
        return;
    if (enemies.checkOvercome(player))
        scoreboard.setScore(scoreboard.getScore() + 1);

    elapsedTime = clock.restart().asSeconds();
    timePassed += elapsedTime;
    auto speed = worldVelocity * elapsedTime * -1.f;
    if (timePassed > spawnInterval)
    {
        enemies.spawn(random.getInt(0, 1));
        timePassed -= spawnInterval;
        minSpawnInterval = std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity;
        spawnInterval = random.getFloat(minSpawnInterval, 2 * minSpawnInterval);

        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldVelocityStep;
            player.setJumpVelocity(player.getJumpVelocity() + playerVelocityStep);
        }
    }

    if (playerVelocity < 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 < player.getJumpHeight())
            playerVelocity *= -1;
    }
    else if (playerVelocity > 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 > background.getGroundHeight())
            playerVelocity = 0;
    }

    if (isCrawling)
    {
        if (!playerVelocity)
        {
            player.setScale(2.f, 0.5f);
            player.setPosition(player.getPosition().x, background.getGroundHeight() - player.getScaledSize().y / 2);
        }
    }
    else
    {
        if (!playerVelocity)
        {
            player.setScale(1.f, 1.f);
            player.setPosition(player.getPosition().x, background.getGroundHeight() - player.getScaledSize().y / 2);
        }
    }
    isCrawling = false;

    background.move(sf::Vector2f(speed, 0));
    enemies.move(sf::Vector2f(speed, 0));
    player.move(sf::Vector2f(0, playerVelocity));
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvent();
        update();
        render();
    }
}

Game::~Game() {}