// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

#include <iostream>

Player::Player(sf::RenderWindow *windowH) : model(windowH),
                                            jumpState(0),
                                            isSliding(false),
                                            run({0, 0}, 2, .5f),
                                            slide({0, TEXTURE_SIZE.y}, 1, 0),
                                            jumpSound(jumpSoundBuffer),
                                            slideSound(slideSoundBuffer)
{
    auto windowSize = windowH->getSize();

    runningSize = {windowSize.x * 0.08f, windowSize.y * 0.3f};
    slidingSize = {runningSize.y, runningSize.x};

    model.setSize(runningSize);
    model.setCurrentAnimation(run);

    loadTexture("../Textures/player.png"); // текстура игрока

    jumpSoundBuffer.loadFromFile("../Sound/jump.wav");
    slideSoundBuffer.loadFromFile("../Sound/slide.wav");
    slideSound.setPitch(3.f);
}

void Player::draw()
{
    model.draw();
}

void Player::move(float elapsedTime)
{
    if (isSliding)
        return;

    model.updateAnimation(elapsedTime);
    auto pos = getPosition().y;

    if (jumpState < 0 and pos <= jumpHeight - getSize().y / 2)
        jumpState = 1;
    else if (jumpState > 0 and pos >= groundLevel - getSize().y / 2)
        jumpState = 0;

    model.move(0, jumpVelocity * jumpState * elapsedTime);
}

void Player::jump()
{
    if (!jumpState and !isSliding)
    {
        jumpState = -1;
        slideSound.stop();
        jumpSound.play();
    }
}

void Player::loadTexture(const std::string &path)
{
    texture.loadFromFile(path);
    model.setTexture(texture);
}

void Player::accelerate()
{
    jumpVelocity += jumpAcceleration;
}

void Player::setSliding(bool flag)
{
    if (flag == isSliding) // нет смысла ставить уже активный флаг
        return;
    if (jumpState and flag) // нельзя скользить в прыжке
        return;

    isSliding = flag;
    if (isSliding)
    {
        jumpSound.stop();
        slideSound.play();
        model.setCurrentAnimation(slide);
        model.setSize(slidingSize);

        setPosition(getPosition().x, groundLevel - getSize().y * 0.3);
    }
    else
    {
        slideSound.stop();
        model.setCurrentAnimation(run);
        model.setSize(runningSize);

        setPosition(getPosition().x, groundLevel - getSize().y * 0.5);
    }
}

const sf::Vector2f &Player::getRunningSize() const
{
    return runningSize;
}

const sf::Vector2f &Player::getSlidingSize() const
{
    return slidingSize;
}

sf::Vector2f Player::getSize() const
{
    return model.getSize();
}

const sf::Vector2f &Player::getPosition() const
{
    return model.getPosition();
}

void Player::setPosition(float x, float y)
{
    model.setPosition(x, y);
}
void Player::setPosition(const sf::Vector2f &pos)
{
    model.setPosition(pos);
}

sf::FloatRect Player::getGlobalBounds() const
{
    return model.getGlobalBounds();
}

sf::FloatRect Player::getLocalBounds() const
{
    return model.getLocalBounds();
}

sf::RenderWindow *Player::getWindowHandler() const
{
    return model.getWindowHandler();
}

void Player::setJumpVelocity(float v)
{
    jumpVelocity = v;
}

float Player::getJumpVelocity() const
{
    return jumpVelocity;
}

void Player::setJumpAcceleration(float a)
{
    jumpAcceleration = a;
}

float Player::getJumpAcceleration() const
{
    return jumpAcceleration;
}

void Player::setMaxJumpVelocity(float mv)
{
    maxJumpVelocity = mv;
}

float Player::getMaxJumpVelocity() const
{
    return maxJumpVelocity;
}

void Player::setJumpHeight(float h)
{
    jumpHeight = h;
}

float Player::getJumpHeight() const
{
    return jumpHeight;
}

void Player::setGroundLevel(float g)
{
    groundLevel = g;
}

float Player::getGroundLevel() const
{
    return groundLevel;
}

void Player::resetJumpState()
{
    jumpState = 0;
}