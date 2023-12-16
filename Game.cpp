#include <SFML/Window/Event.hpp>

#include <iostream>

#include "Game.h"
#include "Model.h"

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style),
      background(window.getSize()),
      player(window.getSize()),
      enemies(window.getSize(), player.getSize()),
      worldVelocity(200),
      worldVelocityStep(worldVelocity * (9.f / 100)), // 9.f/y, where y is at which spawn count we reach max speed if max speed is 10x base speed
      maxWorldVelocity(worldVelocity * 10),
      playerVelocityStep(window.getSize().y * 0.001f * -1 * (9.f / 100))
{
    auto size = window.getSize();

    background.setGroundHeight(size.y * 0.9f);
    background.setRoadSize(sf::Vector2f(size.x, size.y * 0.05f));

    background.setCloudsAmount(3);
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f));

    background.setTreesAmount(11);
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));
    background.init();

    player.setPosition(sf::Vector2f(size.x * 0.15f + player.getSize().x / 2,
                                    background.getGroundHeight() - background.getRoadSize().y / 2 - player.getSize().y / 2));
    player.setColor(sf::Color(0, 255, 0));
    player.setJumpHeight(size.y * 0.5f);
    player.setJumpVelocity(size.y * 0.001f * -1);

    minSpawnInterval = std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity;
    spawnInterval = random.getFloat(minSpawnInterval, 2 * minSpawnInterval);
    enemies.spawn(random.getInt(0, 1), background.getGroundHeight());
}

void Game::processEvent()
{
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
            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                if (playerVelocity > 0)
                    playerVelocity = -1 * player.getJumpVelocity();
                else
                    playerVelocity = player.getJumpVelocity();
                break;
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

    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;
    elapsedTime = clock.restart().asSeconds();
    timePassed += elapsedTime;
    auto speed = worldVelocity * elapsedTime * -1.f;
    if (timePassed > spawnInterval)
    {
        enemies.spawn(random.getInt(0, 1), background.getGroundHeight());
        timePassed -= spawnInterval;
        minSpawnInterval = std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity;
        spawnInterval = random.getFloat(minSpawnInterval, 2 * minSpawnInterval);

        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldVelocityStep;
            player.setJumpVelocity(player.getJumpVelocity() + playerVelocityStep);
        }
    }
    background.move(sf::Vector2f(speed, 0));
    enemies.move(sf::Vector2f(speed, 0));

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