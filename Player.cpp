// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

Player::Player(const sf::String &file)
{
    texture.loadFromFile(file);
    setTexture(texture);
}
Player::~Player() {}

void Player::setJumpVelocity(float v)
{
    jumpVelocity = v;
}

float Player::getJumpVelocity() const
{
    return jumpVelocity;
}

void Player::setJumpHeight(float h)
{
    jumpHeight = h;
}

float Player::getJumpHeight() const
{
    return jumpHeight;
}
