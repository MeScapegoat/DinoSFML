// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "AnimatedModel.hpp"
AnimatedModel::AnimatedModel() {}

AnimatedModel::~AnimatedModel() {}

const std::vector<sf::Texture> *AnimatedModel::getAnimations() const
{
    return animations;
}

void AnimatedModel::setAnimations(std::vector<sf::Texture> *ani)
{
    animations = ani;
}

void AnimatedModel::updateAnimation()
{
    if (currentAnimationID >= animations->size())
        currentAnimationID = 0;
    auto &texture = animations->at(currentAnimationID++);
    setTexture(texture);
}