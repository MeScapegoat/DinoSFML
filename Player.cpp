// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Player.hpp"

Player::Player(sf::RenderWindow *windowH) : model(windowH),
                                            jumpState(0),
                                            isSliding(false)
{
    auto windowSize = windowH->getSize();
    runningSize = {windowSize.x * 0.06f, windowSize.y * 0.2f};
    slidingSize = {runningSize.y, runningSize.x};
    model.setSize(runningSize);
    model.setAnimations(&runningTextures);
}

void Player::move(float elapsedTime, float worldVelocity)
{
    if (isSliding)
        return;

    if (!jumpState)
    {
        model.updateAnimation(elapsedTime, worldVelocity);
        return;
    }

    auto pos = model.sprite.getPosition().y;
    if (jumpState < 0 and pos <= jumpHeight - model.getSize().y / 2)
        jumpState = 1;
    else if (jumpState > 0 and pos >= groundLevel - model.getSize().y / 2)
        jumpState = 0;

    model.sprite.move(sf::Vector2f(0, jumpVelocity * jumpState));
}

void Player::jump()
{
    if (!jumpState)
        jumpState = -1;
}

void Player::loadSlideTexture(const std::string &path)
{
    slideTexture.loadFromFile(path);
}

void Player::loadRunningTextures(const std::vector<sf::String> &paths)
{
    runningTextures.resize(paths.size());
    for (auto n = 0; n < paths.size(); ++n)
        runningTextures[n].loadFromFile(paths[n]);
    model.updateAnimation(0, 1);
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
        model.setTexture(slideTexture);
        model.setSize(slidingSize);
    }
    else
    {
        model.setSize(runningSize);
    }
    model.sprite.setPosition(model.sprite.getPosition().x, groundLevel - model.getSize().y / 2);
}