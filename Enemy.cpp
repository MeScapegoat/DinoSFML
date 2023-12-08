#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(cube);
}

void Enemy::move(const sf::Vector2f &offset)
{
    cube.setPosition(cube.getPosition() + offset);
}

void Enemy::setPosition(const sf::Vector2f &pos)
{
    cube.setPosition(pos);
}