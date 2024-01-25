#pragma once

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

// мое
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
    float jumpVelocity{0};     // скорость прыжка (также скорость падения)
    float jumpAcceleration{0}; // ускорение прыжка
    float maxJumpVelocity{0};  // максимальная скорость прыжка

    float jumpHeight;     // высота прыжка
    float groundLevel{0}; // уровень земли

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

    sf::SoundBuffer jumpSoundBuffer;
    sf::Sound jumpSound;

    sf::SoundBuffer slideSoundBuffer;
    sf::Sound slideSound;
};