#pragma once
#include <SFML/Graphics.hpp>

class Model
{
public:
    Model(const sf::Vector2f &);
    virtual ~Model();

public:
    void draw(sf::RenderWindow &) const;
    virtual void move(const sf::Vector2f &);
    void setPosition(const sf::Vector2f &);
    const sf::Vector2f &getPosition() const;
    void setColor(const sf::Color &);
    const sf::Vector2f &getSize() const;

private:
    sf::RectangleShape rect;
};