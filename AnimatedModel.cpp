// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "AnimatedModel.hpp"

sf::Vector2i TEXTURE_SIZE{300, 300};

AnimatedModel::AnimatedModel(sf::RenderWindow *windowH) : Model(windowH) {}

void AnimatedModel::setCurrentAnimation(const AnimationInfo &animation)
{
    currentAnimation = animation;
    sprite.setTextureRect({currentAnimation.currentTexture, TEXTURE_SIZE});
    sprite.setOrigin(TEXTURE_SIZE.x / 2, TEXTURE_SIZE.y / 2);
}

const AnimationInfo &AnimatedModel::getCurrentAnimation() const
{
    return currentAnimation;
}

void AnimatedModel::updateAnimation(float elapsedTime)
{
    currentAnimation.timer += elapsedTime;
    if (currentAnimation.timer < currentAnimation.interval)
        return;

    currentAnimation.timer -= currentAnimation.interval;
    if (++currentAnimation.currentFrame >= currentAnimation.frames)
        currentAnimation.currentFrame = 0;
    currentAnimation.currentTexture = {currentAnimation.start.x + TEXTURE_SIZE.x * currentAnimation.currentFrame, currentAnimation.start.y};
    sprite.setTextureRect({currentAnimation.currentTexture, TEXTURE_SIZE});
}

void AnimatedModel::setSize(float x, float y)
{
    size = {x, y};
    normalScale = {x / TEXTURE_SIZE.x, y / TEXTURE_SIZE.y};
    sprite.setScale(normalScale);
}

void AnimatedModel::setSize(const sf::Vector2f &s)
{
    setSize(s.x, s.y);
}

void AnimatedModel::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
}