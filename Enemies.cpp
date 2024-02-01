// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemies.hpp"

#include <iostream>

Enemies::Enemies(sf::RenderWindow *windowH, Player *playerH) : windowHandler(windowH), playerHandler(playerH),
                                                               wormAnim({0, 0}, 2, 0.5f),
                                                               batAnim({0, 0}, 2, 0.5f)
{

    auto windowSize = windowHandler->getSize();

    wormSize = sf::Vector2f(windowSize.x * 0.12f, windowSize.y * 0.12f); // размер червяка
    distBetweenEnemies = wormSize.x * 4.f;                               // расстояние между мобами
    wormsAmount = windowSize.x / distBetweenEnemies + 2;                 // макс кол-во червяков
    wormTexture.loadFromFile("../Textures/worm.png");                    // текстуры червяка

    batSize = sf::Vector2f(windowSize.x * 0.13f, windowSize.y * 0.16f); // размер мышей
    batsAmount = windowSize.x / distBetweenEnemies + 2;                 // макс кол-во мышей
    batTexture.loadFromFile("../Textures/bat.png");                     // текстуры летучей мыши
}

void Enemies::restart()
{
    auto playerSize = playerHandler->model.getSize();

    worms.clear();
    availableWorms.clear();
    busyWorms.clear();
    uncheckedWorms.clear();

    worms.reserve(wormsAmount);
    for (auto n = 0; n < wormsAmount; ++n)
    {
        AnimatedModel worm(windowHandler);
        worm.setCurrentAnimation(wormAnim);
        worm.setTexture(wormTexture);
        worm.setSize(wormSize);
        worms.push_back(std::move(worm));
        availableWorms.push_back(&worms[n]);
    }

    bats.clear();
    availableBats.clear();
    busyBats.clear();
    uncheckedBats.clear();

    bats.reserve(batsAmount);
    for (auto n = 0; n < batsAmount; ++n)
    {
        AnimatedModel bat(windowHandler);
        bat.setCurrentAnimation(batAnim);
        bat.setTexture(batTexture);
        bat.setSize(batSize);
        bats.push_back(bat);
        availableBats.push_back(&bats[n]);
    }
}

void Enemies::draw()
{
    for (auto &worm : busyWorms)
        worm->draw();

    for (auto &bat : busyBats)
        bat->draw();
}

void Enemies::move(float x, float y)
{
    for (auto it = busyWorms.begin(); it < busyWorms.end(); ++it)
    {
        auto wormP = *it;
        if (wormP->sprite.getPosition().x + wormP->getSize().x / 2 <= 0)
        {
            availableWorms.push_back(wormP);
            it = busyWorms.erase(it);
        }
        else
            wormP->sprite.move(x, y);
    }

    for (auto it = busyBats.begin(); it < busyBats.end(); ++it)
    {
        auto batP = *it;
        if (batP->sprite.getPosition().x + batP->getSize().x / 2 <= 0)
        {
            availableBats.push_back(batP);
            it = busyBats.erase(it);
        }
        else
            batP->sprite.move(x, y);
    }
}

void Enemies::move(const sf::Vector2f &offset)
{
    move(offset.x, offset.y);
}

bool Enemies::spawn(float elapsedTime)
{
    auto windowSize = windowHandler->getSize();

    spawnTimer += elapsedTime;
    if (spawnTimer < spawnInterval)
        return false;

    spawnTimer -= spawnInterval;
    if (random.getInt(0, 1))
    {
        if (availableWorms.empty())
            return false;
        auto &worm = *availableWorms.front();
        busyWorms.push_back(availableWorms.front());
        uncheckedWorms.push_back(availableWorms.front());
        worm.sprite.setPosition(windowSize.x + worm.getSize().x / 2.f, groundHeight - worm.getSize().y / 2.0f);
        availableWorms.pop_front();
    }
    else
    {
        if (availableBats.empty())
            return false;
        auto playerSize = playerHandler->getRunningSize();
        auto &bat = *availableBats.front();
        busyBats.push_back(availableBats.front());
        uncheckedBats.push_back(availableBats.front());
        bat.sprite.setPosition(windowSize.x + bat.getSize().x / 2.f, playerHandler->jumpHeight);
        availableBats.pop_front();
    }
    return true;
}

float Enemies::getBetweenDistance() const
{
    return distBetweenEnemies;
}

void Enemies::setGroundHeight(float newground)
{
    groundHeight = newground;
}

float Enemies::getGroundHeight() const
{
    return groundHeight;
}

sf::RenderWindow *Enemies::getWindowHandler()
{
    return windowHandler;
}

bool Enemies::checkCrash() const
{
    auto playerHitBox = playerHandler->model.sprite.getGlobalBounds();
    sf::FloatRect intersection;

    for (const auto &bat : busyBats)
    {
        auto batHitBox = bat->sprite.getGlobalBounds();
        batHitBox.width *= 0.9f;

        playerHitBox.intersects(batHitBox, intersection);
        if (intersection.height > playerHitBox.height * 0.15f and intersection.width > playerHitBox.width * 0.1f)
            return true;
    }

    for (const auto &worm : busyWorms)
    {
        auto wormHitBox = worm->sprite.getGlobalBounds();
        wormHitBox.width *= 0.9f;

        playerHitBox.intersects(wormHitBox, intersection);
        if (intersection.height > playerHitBox.height * 0.15f and intersection.width > playerHitBox.width * 0.1f)
            return true;
    }
    return false;
}

bool Enemies::checkOvercome()
{
    auto playerBorder = playerHandler->model.sprite.getPosition().x - playerHandler->model.getSize().x / 2;
    if (!uncheckedBats.empty())
    {
        auto bat = uncheckedBats.front();
        auto enemyBorder = bat->sprite.getPosition().x + bat->getSize().x / 2;
        if (enemyBorder < playerBorder)
        {
            uncheckedBats.pop_front();
            return true;
        }
    }

    if (!uncheckedWorms.empty())
    {
        auto worm = uncheckedWorms.front();
        auto enemyBorder = worm->sprite.getPosition().x + worm->getSize().x / 2;
        if (enemyBorder < playerBorder)
        {
            uncheckedWorms.pop_front();
            return true;
        }
    }

    return false;
}

void Enemies::loadBatTexture(const sf::String &path)
{
    batTexture.loadFromFile(path);
}

void Enemies::loadWormTexture(const sf::String &path)
{
    wormTexture.loadFromFile(path);
}

void Enemies::updateAnimations(float elapsedTime)
{
    for (auto &worm : busyWorms)
        worm->updateAnimation(elapsedTime);

    for (auto &bat : busyBats)
        bat->updateAnimation(elapsedTime);
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
    spawnInterval = random.getFloat(minSpawnInterval, 1.5f * minSpawnInterval);
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

const sf::Vector2f &Enemies::getWormSize() const
{
    return wormSize;
}

const sf::Vector2f &Enemies::getBatSize() const
{
    return batSize;
}