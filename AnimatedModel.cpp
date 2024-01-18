// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "AnimatedModel.hpp"
AnimatedModel::AnimatedModel(sf::RenderWindow *windowH) : Model(windowH) {}

const std::vector<sf::Texture> *AnimatedModel::getAnimations() const
{
    return animations;
}

void AnimatedModel::setAnimations(std::vector<sf::Texture> *ani)
{
    animations = ani;
}

void AnimatedModel::updateAnimation(float elapsedTime, float worldVelocity)
{
    if (!animationInterval)
    {
        animationDistance = getSize().x / 2.0f;
        animationInterval = animationDistance / worldVelocity;
    }
    animationTimer += elapsedTime;

    if (animationTimer < animationInterval)
        return;
    animationTimer -= animationInterval;
    animationInterval = animationDistance / worldVelocity;
    if (currentAnimationID == animations->size())
        currentAnimationID = 0;
    setTexture(animations->at(currentAnimationID++));
}