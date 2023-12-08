#include "Game.h"

#include <iostream>

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style), background(window.getSize(), 20, 20), velocity(-400, 0)
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
    while (window.isOpen())
    {
        processEvent();
        update();
        render();
    }
}

Game::~Game() {}