#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedModel.hpp"

class Player
{
public:
    Player(sf::RenderWindow *);
    ~Player() = default;

public:
    void move(float);
    void jump();

    void loadTexture(const std::string &);

    void setSliding(bool);

    const sf::Vector2f &getRunningSize() const;
    const sf::Vector2f &getSlidingSize() const;

public:
    float jumpVelocity{0};
    float jumpVelocityStep{0};
    float maxJumpVelocity{0};

    float jumpHeight;
    float groundLevel{0};

    AnimatedModel model;

private:
    AnimationInfo run;
    AnimationInfo slide;

    // Текущее "состояние" прыжка, -1 если движемся вверх, 1 если движемся вниз, 0 если бежим по прямой (нет прыжка)
    int jumpState;

    bool isSliding;

    sf::Vector2f runningSize;
    sf::Vector2f slidingSize;

    sf::Texture texture;
};