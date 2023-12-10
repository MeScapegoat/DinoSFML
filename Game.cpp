#include "Game.h"
#include "Model.h"

#include <iostream>

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style), background(window.getSize()), velocity(-500, 0),
      player(sf::Vector2f(50, 100)), enemies(window.getSize(), player.getSize())
{
    spawnInterval = std::max(enemies.getFlyingDistance() / -velocity.x, enemies.getGroundDistance() / -velocity.x);
    player.setColor(sf::Color(0, 255, 0));
}

void Game::processEvent()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
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
    std::cout << timePassed << "\n";
    if (timePassed > spawnInterval)
    {
        enemies.spawn(type, background.getGroundHeight());
        type = -type;
        timePassed -= spawnInterval;
    }
    auto speed = velocity * elapsedTime;

    background.move(speed);
    enemies.move(speed);
}

void Game::run()
{
    auto size = window.getSize();
    background.setGroundHeight(size.y * 0.9f);

    background.setCloudsAmount(4);
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f));

    background.setTreesAmount(12);
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));
    background.init();

    player.setPosition(sf::Vector2f(size.x * 0.15f + player.getSize().x / 2,
                                    background.getGroundHeight() - background.getRoadSize().y / 2 - player.getSize().y / 2));
    enemies.spawn(1, background.getGroundHeight());
    while (window.isOpen())
    {
        processEvent();
        update();
        render();
    }
}

Game::~Game() {}