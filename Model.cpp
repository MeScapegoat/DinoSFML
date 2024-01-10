// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Model.hpp"

Model::Model() {}

Model::~Model() {}

sf::Vector2f Model::getSize() const
{
    auto scale = getScale();
    return {size.x * scale.x, size.y * scale.y};
}

void Model::setSize(float x, float y)
{
    size = {x, y};
    if (!getTexture())
        return;
    auto textureSize = getTexture()->getSize();
    normalScale = {size.x / textureSize.x, size.y / textureSize.y};
    sprite.setScale(normalScale);
}

void Model::setSize(sf::Vector2f size)
{
    setSize(size.x, size.y);
}

#include <iostream>
void Model::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    auto textureSize = texture.getSize();
    normalScale = {size.x / textureSize.x, size.y / textureSize.y};
    sprite.setScale(normalScale);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

const sf::Texture *Model::getTexture() const
{
    return sprite.getTexture();
}

void Model::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Model::move(float x, float y)
{
    sprite.move(x, y);
}

void Model::move(const sf::Vector2f &offset)
{
    sprite.move(offset);
}

void Model::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Model::setPosition(const sf::Vector2f &pos)
{
    sprite.setPosition(pos);
}

const sf::Vector2f &Model::getPosition() const
{
    return sprite.getPosition();
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

sf::FloatRect Model::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

sf::FloatRect Model::getLocalBound() const
{
    return sprite.getLocalBounds();
}