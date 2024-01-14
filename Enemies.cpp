// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemies.hpp"

#include <iostream>

Enemies::Enemies(sf::Vector2u windowSize) : windowSize(std::move(windowSize)) {}

void Enemies::init()
{
    groundEnemySize = sf::Vector2f(windowSize.x * 0.2f, windowSize.y * 0.2f);
    distBetweenGroundEnemies = playerSize.x + groundEnemySize.x;
    groundEnemiesAmount = windowSize.x / distBetweenGroundEnemies + 2;

    flyingEnemySize = sf::Vector2f(windowSize.x * 0.2f, windowSize.y * 0.2f);
    distBetweenFlyingEnemies = playerSize.x + flyingEnemySize.x;
    flyingEnemiesAmount = windowSize.x / distBetweenFlyingEnemies + 2;

    uncheckedGroundEnemies.clear();
    busyGroundEnemies.clear();
    groundEnemies.clear();
    groundEnemies.reserve(groundEnemiesAmount);
    unsigned textureID = 0;
    for (auto n = 0; n < groundEnemiesAmount; ++n)
    {
        AnimatedModel groundEnemy;
        groundEnemy.setAnimations(&groundEnemiesTextures);
        if (textureID == groundEnemiesTextures.size())
            textureID = 0;
        groundEnemy.setTexture(groundEnemiesTextures[textureID++]);
        groundEnemy.setSize(groundEnemySize);
        groundEnemies.push_back(std::move(groundEnemy));
        availableGroundEnemies.push_back(&groundEnemies[n]);
    }

    uncheckedFlyingEnemies.clear();
    busyFlyingEnemies.clear();
    flyingEnemies.clear();
    flyingEnemies.reserve(flyingEnemiesAmount);
    textureID = 0;
    for (auto n = 0; n < flyingEnemiesAmount; ++n)
    {
        AnimatedModel flyingEnemy;
        flyingEnemy.setAnimations(&flyingEnemiesTextures);
        if (textureID == flyingEnemiesTextures.size())
            textureID = 0;
        flyingEnemy.setTexture(flyingEnemiesTextures[textureID++]);
        flyingEnemy.setSize(flyingEnemySize);
        flyingEnemies.push_back(flyingEnemy);
        availableFlyingEnemies.push_back(&flyingEnemies[n]);
    }
    flyingAnimationDistance = flyingEnemies.front().getSize().x * 1;
    groundAnimationDistance = groundEnemies.front().getSize().x * 1;

    flyingAnimationInterval = flyingAnimationDistance / 200;
    groundAnimationInterval = groundAnimationDistance / 200;
}

Enemies::~Enemies() {}

void Enemies::draw(sf::RenderWindow &window) const
{
    for (auto &groundEnemy : busyGroundEnemies)
        groundEnemy->draw(window);

    for (auto &flyingEnemy : busyFlyingEnemies)
        flyingEnemy->draw(window);
}

void Enemies::move(const sf::Vector2f &offset)
{
    for (auto it = busyGroundEnemies.begin(); it < busyGroundEnemies.end(); ++it)
    {
        auto groundEnemyP = *it;
        if (groundEnemyP->getPosition().x + groundEnemyP->getSize().x / 2 <= 0)
        {
            availableGroundEnemies.push_back(groundEnemyP);
            it = busyGroundEnemies.erase(it);
        }
        else
            groundEnemyP->move(offset);
    }

    for (auto it = busyFlyingEnemies.begin(); it < busyFlyingEnemies.end(); ++it)
    {
        auto flyingEnemyP = *it;
        if (flyingEnemyP->getPosition().x + flyingEnemyP->getSize().x / 2 <= 0)
        {
            availableFlyingEnemies.push_back(flyingEnemyP);
            it = busyFlyingEnemies.erase(it);
        }
        else
            flyingEnemyP->move(offset);
    }
}

bool Enemies::spawn(float elapsedTime)
{
    spawnTimer += elapsedTime;
    if (spawnTimer < spawnInterval)
        return false;

    spawnTimer -= spawnInterval;
    if (random.getInt(0, 1))
    {
        auto &groundEnemy = *availableGroundEnemies.front();
        busyGroundEnemies.push_back(availableGroundEnemies.front());
        uncheckedGroundEnemies.push_back(availableGroundEnemies.front());
        groundEnemy.setPosition(windowSize.x + groundEnemy.getSize().x / 2.f, groundHeight - groundEnemy.getSize().y / 2.0f);
        availableGroundEnemies.pop_front();
    }
    else
    {
        auto &flyingEnemy = *availableFlyingEnemies.front();
        busyFlyingEnemies.push_back(availableFlyingEnemies.front());
        uncheckedFlyingEnemies.push_back(availableFlyingEnemies.front());
        flyingEnemy.setPosition(windowSize.x + flyingEnemy.getSize().x / 2.f, groundHeight - playerSize.y / 2.f - flyingEnemy.getSize().y / 2.f);
        availableFlyingEnemies.pop_front();
    }
    return true;
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

    for (const auto &flying : busyFlyingEnemies)
    {
        auto eR = flying->getGlobalBounds();
        if (pR.intersects(eR))
            return true;
    }

    for (const auto &ground : busyGroundEnemies)
    {
        auto eR = ground->getGlobalBounds();
        if (pR.intersects(eR))
            return true;
    }
    return false;
}

bool Enemies::checkOvercome(const Player &player)
{
    auto playerborder = player.getPosition().x - player.getSize().x / 2;
    if (!uncheckedFlyingEnemies.empty())
    {
        auto flying = uncheckedFlyingEnemies.front();
        auto enemyborder = flying->getPosition().x + flying->getSize().x / 2;
        if (enemyborder < playerborder)
        {
            uncheckedFlyingEnemies.pop_front();
            return true;
        }
    }

    if (!uncheckedGroundEnemies.empty())
    {
        auto ground = uncheckedGroundEnemies.front();
        auto enemyborder = ground->getPosition().x + ground->getSize().x / 2;
        if (enemyborder < playerborder)
        {
            uncheckedGroundEnemies.pop_front();
            return true;
        }
    }

    return false;
}

void Enemies::setPlayerSize(sf::Vector2f size)
{
    playerSize = size;
}

sf::Vector2f Enemies::getPlayerSize() const
{
    return playerSize;
}

void Enemies::loadFlyingEnemiesTextures(const std::vector<sf::String> &files)
{
    for (auto &file : files)
    {
        sf::Texture texture;
        texture.loadFromFile(file);
        flyingEnemiesTextures.push_back(texture);
    }
}

void Enemies::loadGroundEnemiesTextures(const std::vector<sf::String> &files)
{
    for (auto &file : files)
    {
        sf::Texture texture;
        texture.loadFromFile(file);
        groundEnemiesTextures.push_back(texture);
    }
}

void Enemies::updateAnimations(float elapsedTime, float velocity)
{
    flyingAnimationTimer += elapsedTime;
    groundAnimationTimer += elapsedTime;
    if (flyingAnimationTimer > flyingAnimationInterval)
    {
        flyingAnimationTimer -= flyingAnimationInterval;
        flyingAnimationInterval = flyingAnimationDistance / velocity;
        for (auto &Enemy : busyGroundEnemies)
            Enemy->updateAnimation();
    }

    if (groundAnimationTimer > groundAnimationInterval)
    {
        groundAnimationTimer -= groundAnimationInterval;
        groundAnimationInterval = groundAnimationDistance / velocity;
        for (auto &Enemy : busyFlyingEnemies)
            Enemy->updateAnimation();
    }
}

void Enemies::setSpawnTimer(float value)
{
    spawnTimer = value;
}

float Enemies::getSpawnTimer() const
{
    return spawnTimer;
}

void Enemies::setMinSpawnInterval(float value)
{
    minSpawnInterval = value;
    spawnInterval = random.getFloat(minSpawnInterval, 2 * minSpawnInterval);
}

float Enemies::getMinSpawnInterval() const
{
    return minSpawnInterval;
}

void Enemies::setSpawnInterval(float value)
{
    spawnInterval = value;
}

float Enemies::getSpawnInterval() const
{
    return spawnInterval;
}