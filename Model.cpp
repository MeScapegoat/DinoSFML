#include "Model.hpp"

Model::Model(const sf::Vector2f &size) : RectangleShape(size)
{
    setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
}

Model::~Model() {}

void Model::draw(sf::RenderWindow &window) const
{
    window.draw(*this);
}

sf::Vector2f Model::getScaledSize() const
{
    auto size = getSize();
    auto scale = getScale();
    return sf::Vector2f(size.x * scale.x, size.y * scale.y);
}