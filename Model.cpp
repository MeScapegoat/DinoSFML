// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Model.hpp"

Model::Model(sf::RenderWindow *windowH) : windowHandler(windowH) {}

sf::Vector2f Model::getSize() const
{
    return size;
}

void Model::setSize(float x, float y)
{
    size = {x, y};
    if (!sprite.getTexture())
        return;
    auto textureSize = sprite.getTexture()->getSize();
    normalScale = {size.x / textureSize.x, size.y / textureSize.y};
    sprite.setScale(normalScale);
}

void Model::setSize(const sf::Vector2f &s)
{
    setSize(s.x, s.y);
}

void Model::setTexture(const sf::Texture &texture)
{
    auto textureSize = texture.getSize();
    sprite.setTexture(texture);
    sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    normalScale = {size.x / textureSize.x, size.y / textureSize.y};
    sprite.setScale(normalScale);
}

void Model::draw()
{
    windowHandler->draw(sprite);
}

void Model::setScale(float x, float y)
{
    sprite.setScale(x * normalScale.x, y * normalScale.y);
}

void Model::setScale(const sf::Vector2f &scale)
{
    setScale(scale.x, scale.y);
}

sf::Vector2f Model::getScale() const
{
    auto scale = sprite.getScale();
    return {scale.x / normalScale.x, scale.y / normalScale.y};
}