// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

Player::Player(/*const std::vector<std::string> &,*/ const std::string &slidePath)
{
    slideTexture.loadFromFile(slidePath);
}
Player::~Player() {}

void Player::setCurrentJumpVelocity(float v)
{
    currentJumpVelocity = v;
}

float Player::getCurrentJumpVelocity() const
{
    return currentJumpVelocity;
}

void Player::setJumpVelocity(float v)
{
    jumpVelocity = v;
}

float Player::getJumpVelocity() const
{
    return jumpVelocity;
}

void Player::setJumpVelocityStep(float v)
{
    jumpVelocityStep = v;
}

float Player::getJumpVelocityStep() const
{
    return jumpVelocityStep;
}

void Player::setJumpHeight(float h)
{
    jumpHeight = h;
}

float Player::getJumpHeight() const
{
    return jumpHeight;
}

sf::Vector2f Player::getPosition() const
{
    return model.getPosition();
}
sf::Vector2f Player::getSize() const
{
    return model.getSize();
}