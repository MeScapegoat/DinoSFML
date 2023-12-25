// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

Player::Player(const sf::Vector2u &size) : Model(sf::Vector2f(size.x * 0.03f, size.y * 0.1f)) {}
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