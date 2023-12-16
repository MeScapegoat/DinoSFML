#include "Enemies.h"

#include <iostream>

Enemies::Enemies(sf::Vector2u windowSize, sf::Vector2f playerSize)
    : windowSize(std::move(windowSize)), playerSize(std::move(playerSize))
{
    groundEnemySize = sf::Vector2f(windowSize.x * 0.1f, windowSize.y * 0.1f);
    groundEnemyColor = sf::Color::Red;
    distBetweenGroundEnemies = playerSize.x + groundEnemySize.x;
    groundEnemiesAmount = windowSize.x / distBetweenGroundEnemies + 2;
    groundEnemies.reserve(groundEnemiesAmount);
    for (auto n = 0; n < groundEnemiesAmount; ++n)
    {
        Model groundEnemy(groundEnemySize);
        groundEnemy.setColor(groundEnemyColor);
        groundEnemies.push_back(std::move(groundEnemy));
        availableGroundEnemies.push_back(&groundEnemies[n]);
    }

    flyingEnemySize = sf::Vector2f(windowSize.x * 0.2f, windowSize.y * 0.1f);
    flyingEnemyColor = sf::Color::Cyan;
    distBetweenFlyingEnemies = playerSize.x + flyingEnemySize.x;
    flyingEnemiesAmount = windowSize.x / distBetweenFlyingEnemies + 2;
    flyingEnemies.reserve(flyingEnemiesAmount);
    for (auto n = 0; n < flyingEnemiesAmount; ++n)
    {
        Model flyingEnemy(flyingEnemySize);
        flyingEnemy.setColor(flyingEnemyColor);
        flyingEnemies.push_back(flyingEnemy);
        availableFlyingEnemies.push_back(&flyingEnemies[n]);
    }
}

Enemies::~Enemies() {}

void Enemies::draw(sf::RenderWindow &window) const
{
    for (auto &groundEnemy : BusyGroundEnemies)
        groundEnemy->draw(window);

    for (auto &flyingEnemy : BusyFlyingEnemies)
        flyingEnemy->draw(window);
}

void Enemies::move(const sf::Vector2f &offset)
{
    for (auto it = BusyGroundEnemies.begin(); it < BusyGroundEnemies.end(); ++it)
    {
        auto groundEnemyP = *it;
        if (groundEnemyP->getPosition().x + groundEnemyP->getSize().x / 2 <= 0)
        {
            availableGroundEnemies.push_back(groundEnemyP);
            it = BusyGroundEnemies.erase(it);
        }
        else
            groundEnemyP->move(offset);
    }

    for (auto it = BusyFlyingEnemies.begin(); it < BusyFlyingEnemies.end(); ++it)
    {
        auto flyingEnemyP = *it;
        if (flyingEnemyP->getPosition().x + flyingEnemyP->getSize().x / 2 <= 0)
        {
            availableFlyingEnemies.push_back(flyingEnemyP);
            it = BusyFlyingEnemies.erase(it);
        }
        else
            flyingEnemyP->move(offset);
    }
}

void Enemies::spawn(int type, unsigned ground)
{
    if (type > 0)
    {
        auto &groundEnemy = *availableGroundEnemies.front();
        BusyGroundEnemies.push_back(availableGroundEnemies.front());
        groundEnemy.setPosition(sf::Vector2f(windowSize.x + groundEnemy.getSize().x / 2, ground - groundEnemy.getSize().y));
        availableGroundEnemies.pop_front();
    }
    else
    {
        auto &flyingEnemy = *availableFlyingEnemies.front();
        BusyFlyingEnemies.push_back(availableFlyingEnemies.front());
        flyingEnemy.setPosition(sf::Vector2f(windowSize.x + flyingEnemy.getSize().x / 2, ground - 5 * flyingEnemy.getSize().y));
        availableFlyingEnemies.pop_front();
    }
}

float Enemies::getGroundDistance() const
{
    return distBetweenGroundEnemies;
}

float Enemies::getFlyingDistance() const
{
    return distBetweenFlyingEnemies;
}