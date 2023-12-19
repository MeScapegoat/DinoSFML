#include "Enemies.hpp"

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
        groundEnemy.setFillColor(groundEnemyColor);
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
        flyingEnemy.setFillColor(flyingEnemyColor);
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

void Enemies::spawn(int type)
{
    if (type > 0)
    {
        auto &groundEnemy = *availableGroundEnemies.front();
        BusyGroundEnemies.push_back(availableGroundEnemies.front());
        uncheckedGroundEnemies.push_back(availableGroundEnemies.front());
        groundEnemy.setPosition(windowSize.x + groundEnemy.getSize().x / 2, groundHeight - groundEnemy.getSize().y * 0.8);
        availableGroundEnemies.pop_front();
    }
    else
    {
        auto &flyingEnemy = *availableFlyingEnemies.front();
        BusyFlyingEnemies.push_back(availableFlyingEnemies.front());
        uncheckedFlyingEnemies.push_back(availableFlyingEnemies.front());
        flyingEnemy.setPosition(windowSize.x + flyingEnemy.getSize().x / 2, groundHeight - 5 * flyingEnemy.getSize().y * 0.8);
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

void Enemies::setGroundHeight(float newground)
{
    groundHeight = newground;
}

float Enemies::getGroundHeight() const
{
    return groundHeight;
}

bool Enemies::checkCrash(const Player &player) const
{
    auto pR = player.getGlobalBounds();

    for (const auto &flying : BusyFlyingEnemies)
    {
        auto eR = flying->getGlobalBounds();
        if (pR.intersects(eR))
            return true;
    }

    for (const auto &ground : BusyGroundEnemies)
    {
        auto eR = ground->getGlobalBounds();
        if (pR.intersects(eR))
            return true;
    }
    return false;
}

bool Enemies::checkOvercome(const Player &player)
{
    auto playerBorder = player.getPosition().x - player.getScaledSize().x / 2;
    if (!uncheckedFlyingEnemies.empty())
    {
        auto flying = uncheckedFlyingEnemies.front();
        auto enemyBorder = flying->getPosition().x + flying->getSize().x / 2;
        if (enemyBorder < playerBorder)
        {
            uncheckedFlyingEnemies.pop_front();
            return true;
        }
    }

    if (!uncheckedGroundEnemies.empty())
    {
        auto ground = uncheckedGroundEnemies.front();
        auto enemyBorder = ground->getPosition().x + ground->getSize().x / 2;
        if (enemyBorder < playerBorder)
        {
            uncheckedGroundEnemies.pop_front();
            return true;
        }
    }

    return false;
}