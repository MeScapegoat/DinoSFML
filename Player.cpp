// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

#include <iostream>

Player::Player(sf::RenderWindow *windowH) : model(windowH),
                                            jumpState(0),
                                            isSliding(false),
                                            jumpHeight(windowH->getSize().y * 0.5f),
                                            run({0, 0}, 2, .5f),
                                            slide({0, TEXTURE_SIZE.y}, 1, 0),
                                            jumpSound(jumpSoundBuffer),
                                            slideSound(slideSoundBuffer)
{
    auto windowSize = windowH->getSize();

    runningSize = {windowSize.x * 0.1f, windowSize.y * 0.3f};
    slidingSize = {runningSize.y, runningSize.x};

    model.setSize(runningSize);
    model.setCurrentAnimation(run);

    loadTexture("../Textures/player.png"); // текстура игрока

    jumpSoundBuffer.loadFromFile("../Sound/jump.wav");
    slideSoundBuffer.loadFromFile("../Sound/slide.wav");
}

void Player::move(float elapsedTime)
{
    if (isSliding)
        return;

    model.updateAnimation(elapsedTime);
    auto pos = model.sprite.getPosition().y;

    if (jumpState < 0 and pos <= jumpHeight - model.getSize().y / 2)
        jumpState = 1;
    else if (jumpState > 0 and pos >= groundLevel - model.getSize().y / 2)
        jumpState = 0;

    model.sprite.move(sf::Vector2f(0, jumpVelocity * jumpState * elapsedTime));
}

void Player::jump()
{
    if (!jumpState)
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

        model.sprite.setPosition(model.sprite.getPosition().x, groundLevel - model.getSize().y * 0.3);
    }
    else
    {
        slideSound.stop();
        model.setCurrentAnimation(run);
        model.setSize(runningSize);

        model.sprite.setPosition(model.sprite.getPosition().x, groundLevel - model.getSize().y * 0.5);
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
