#include "Game.h"

#include <iostream>

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style) : window(mode, title, style), ct(window.getSize().x, window.getSize().y)
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

    for (const auto &trail : ct.trails)
        window.draw(trail);
    window.draw(ct.rectangle);
    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;

    if ((ct.velocity.x > 0 and (ct.rectangle.getPosition().x + ct.rectangle.getSize().x / 2) > window.getSize().x) or
        (ct.velocity.x < 0 and (ct.rectangle.getPosition().x - ct.rectangle.getSize().x / 2) < 0))
        ct.velocity.x = -ct.velocity.x;

    if ((ct.velocity.y > 0 and (ct.rectangle.getPosition().y + ct.rectangle.getSize().y / 2) > window.getSize().y) or
        (ct.velocity.y < 0 and (ct.rectangle.getPosition().y - ct.rectangle.getSize().y / 2) < 0))
        ct.velocity.y = -ct.velocity.y;

    ct.trail.setPosition(ct.rectangle.getPosition());

    for (auto start = ct.trails.begin(); start != ct.trails.end(); ++start)
    {
        auto size = start->getSize();
        size.x -= ct.decX;
        size.y -= ct.decY;
        start->setSize(size);
        auto color = start->getFillColor();
        if (!ct.iteration)
            color.a -= 1;
        if (color.a)
            start->setFillColor(color);
        else
            ct.trails.erase(start);
    }

    ct.trail.setFillColor(ct.trailColor);
    ct.trails.push_back(ct.trail);
    ct.rectangle.setPosition(ct.rectangle.getPosition() + ct.velocity);

    ct.iteration = (ct.iteration + 1) % ct.cap;
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