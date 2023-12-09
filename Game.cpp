#include "Game.h"

#include <iostream>

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style), background(window.getSize()), velocity(-100, 0)
{
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

    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;
    auto elapsed = clock.restart().asSeconds();
    background.move(velocity * elapsed);
}

void Game::run()
{
    auto size = window.getSize();
    background.setGroundHeight(size.y * 1.f);

    background.setCloudsAmount(4);
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f));

    background.setTreesAmount(16);
    background.setTreeSize(sf::Vector2f(size.x * 0.03f, size.y * 0.3f));
    background.init();
    while (window.isOpen())
    {
        processEvent();
        update();
        render();
    }
}

Game::~Game() {}