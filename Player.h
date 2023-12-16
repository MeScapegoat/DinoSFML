#pragma once

#include <SFML/Graphics.hpp>

#include "Model.h"

class Player : public Model
{
public:
    Player(const sf::Vector2u &);
    ~Player();

public:
    void setJumpVelocity(float);
    float getJumpVelocity() const;

    void setJumpHeight(float);
    float getJumpHeight() const;

private:
    float jumpVelocity;
    float jumpHeight;
};