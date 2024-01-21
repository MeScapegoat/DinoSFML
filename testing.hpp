#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
struct test
{
    test(const sf::String &path, sf::RenderWindow *window) : window(window)
    {
        texture.loadFromFile(path);

        auto textureSize = texture.getSize();
        auto windowSize = window->getSize();

        sf::Vector2f size = {400, 400};
        sf::Vector2f halfSize = {size.x / 2.0, size.y / 2.0};
        sf::Vector2f halfWindowSize = {windowSize.x / 2.0, windowSize.y / 2.0};
        sf::Vector2f scale = {size.x / textureSize.x, size.y / textureSize.y};

        sprite.setTexture(texture);
        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
        sprite.setScale(scale);
        sprite.setPosition(halfWindowSize);

        back.setSize(static_cast<sf::Vector2f>(size) * 1.f);
        back.setOrigin(back.getSize().x / 2.0f, back.getSize().y / 2.0f);
        back.setFillColor(sf::Color::Green);
        back.setPosition(halfWindowSize);
    }

    void draw()
    {
        window->draw(back);
        window->draw(sprite);
    }

public:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape back;
    sf::RenderWindow *window;
};