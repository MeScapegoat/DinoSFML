#pragma once
#include <SFML/Graphics.hpp>

class Model
{
public:
    Model();
    Model(const sf::Vector2f &);
    virtual ~Model();

public:
    virtual void draw(sf::RenderWindow &) const;
    virtual void move(const sf::Vector2f &);
    virtual void setPosition(const sf::Vector2f &);
    virtual const sf::Vector2f &getPosition() const;
    virtual void setColor(const sf::Color &);
    virtual const sf::Vector2f &getSize() const;
    virtual void setSize(const sf::Vector2f &);

private:
    sf::RectangleShape rect;
};