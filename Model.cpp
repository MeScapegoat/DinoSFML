#include "Model.h"

Model::Model(const sf::Vector2f &size) : rect(size)
{
    rect.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    rect.setPosition(0, 0);
}

Model::~Model() {}

void Model::draw(sf::RenderWindow &window) const
{
    window.draw(rect);
}

void Model::move(const sf::Vector2f &offset)
{
    rect.move(offset);
}

void Model::setPosition(const sf::Vector2f &pos)
{
    rect.setPosition(pos);
}

const sf::Vector2f &Model::getPosition() const
{
    return rect.getPosition();
}

void Model::setColor(const sf::Color &color)
{
    rect.setFillColor(color);
}

const sf::Vector2f &Model::getSize() const
{
    return rect.getSize();
}