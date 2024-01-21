// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemies.hpp"

#include <iostream>

Enemies::Enemies(sf::RenderWindow *windowH, Player *playerH) : windowHandler(windowH), playerHandler(playerH),
                                                               wormAnim({0, 0}, 2, 0.5f),
                                                               batAnim({0, 0}, 2, 0.5f)
{
    batTexture.loadFromFile("../Textures/bat.png");   // текстуры летучей мыши
    wormTexture.loadFromFile("../Textures/worm.png"); // текстуры червяка
}

void Enemies::init()
{
    auto windowSize = windowHandler->getSize();
    auto playerSize = playerHandler->model.getSize();

    wormSize = sf::Vector2f(windowSize.x * 0.2f, windowSize.y * 0.2f);
    distBetweenWorms = playerSize.x + wormSize.x;
    wormsAmount = windowSize.x / distBetweenWorms + 2;

    batSize = sf::Vector2f(windowSize.x * 0.2f, windowSize.y * 0.2f);
    distBetweenBats = playerSize.x + batSize.x;
    batsAmount = windowSize.x / distBetweenBats + 2;

    uncheckedWorms.clear();
    busyWorms.clear();
    worms.clear();

    worms.reserve(wormsAmount);
    unsigned textureID = 0;
    for (auto n = 0; n < wormsAmount; ++n)
    {
        AnimatedModel worm(windowHandler);
        worm.setCurrentAnimation(wormAnim);
        worm.setTexture(wormTexture);
        worm.setSize(batSize);
        worms.push_back(std::move(worm));
        availableWorms.push_back(&worms[n]);
    }

    uncheckedBats.clear();
    busyBats.clear();
    bats.clear();
    bats.reserve(batsAmount);
    textureID = 0;
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
    for (auto &groundEnemy : busyWorms)
        groundEnemy->draw();

    for (auto &flyingEnemy : busyBats)
        flyingEnemy->draw();
}

void Enemies::move(float x, float y)
{
    for (auto it = busyWorms.begin(); it < busyWorms.end(); ++it)
    {
        auto groundEnemyP = *it;
        if (groundEnemyP->sprite.getPosition().x + groundEnemyP->getSize().x / 2 <= 0)
        {
            availableWorms.push_back(groundEnemyP);
            it = busyWorms.erase(it);
        }
        else
            groundEnemyP->sprite.move(x, y);
    }

    for (auto it = busyBats.begin(); it < busyBats.end(); ++it)
    {
        auto flyingEnemyP = *it;
        if (flyingEnemyP->sprite.getPosition().x + flyingEnemyP->getSize().x / 2 <= 0)
        {
            availableBats.push_back(flyingEnemyP);
            it = busyBats.erase(it);
        }
        else
            flyingEnemyP->sprite.move(x, y);
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
        auto &groundEnemy = *availableWorms.front();
        busyWorms.push_back(availableWorms.front());
        uncheckedWorms.push_back(availableWorms.front());
        groundEnemy.sprite.setPosition(windowSize.x + groundEnemy.getSize().x / 2.f, groundHeight - groundEnemy.getSize().y / 2.0f);
        availableWorms.pop_front();
    }
    else
    {
        auto playerSize = playerHandler->getRunningSize();
        auto &flyingEnemy = *availableBats.front();
        busyBats.push_back(availableBats.front());
        uncheckedBats.push_back(availableBats.front());
        flyingEnemy.sprite.setPosition(windowSize.x + flyingEnemy.getSize().x / 2.f, groundHeight - playerSize.y / 2.f - flyingEnemy.getSize().y / 2.f);
        availableBats.pop_front();
    }
    return true;
}

float Enemies::getWormDistance() const
{
    return distBetweenWorms;
}

float Enemies::getBatDistance() const
{
    return distBetweenBats;
}

void Enemies::setGroundHeight(float newground)
{
    groundHeight = newground;
}

float Enemies::getGroundHeight() const
{
    return groundHeight;
}

void Enemies::setWindowHandler(sf::RenderWindow *windowH)
{
    windowHandler = windowH;
    // обработать все модели размеры и прочее в соответствии с новым окном
}

sf::RenderWindow *Enemies::getWindowHandler()
{
    return windowHandler;
}

bool Enemies::checkCrash() const
{
    auto playerHitBox = playerHandler->model.sprite.getGlobalBounds();
    float yScale = playerHitBox.height * 0.1f;
    float xScale = playerHitBox.width * 0.1f;
    playerHitBox.left += xScale;
    playerHitBox.width -= xScale * 2;
    playerHitBox.top += yScale;
    playerHitBox.height -= yScale * 2;

    for (const auto &bat : busyBats)
    {
        auto batHitBox = bat->sprite.getGlobalBounds();
        yScale = batHitBox.height * 0.1f;
        xScale = batHitBox.width * 0.1f;
        batHitBox.left += xScale;
        batHitBox.width -= xScale * 2;
        batHitBox.top += yScale;
        batHitBox.height -= yScale * 2;

        if (playerHitBox.intersects(batHitBox))
            return true;
    }

    for (const auto &worm : busyWorms)
    {
        auto wormHitBox = worm->sprite.getGlobalBounds();
        yScale = wormHitBox.height * 0.1f;
        xScale = wormHitBox.width * 0.1f;
        wormHitBox.left += xScale;
        wormHitBox.width -= xScale * 2;
        wormHitBox.top += yScale;
        wormHitBox.height -= yScale * 2;

        if (playerHitBox.intersects(wormHitBox))
            return true;
    }
    return false;
}

bool Enemies::checkOvercome()
{
    auto playerborder = playerHandler->model.sprite.getPosition().x - playerHandler->model.getSize().x / 2;
    if (!uncheckedBats.empty())
    {
        auto flying = uncheckedBats.front();
        auto enemyborder = flying->sprite.getPosition().x + flying->getSize().x / 2;
        if (enemyborder < playerborder)
        {
            uncheckedBats.pop_front();
            return true;
        }
    }

    if (!uncheckedWorms.empty())
    {
        auto ground = uncheckedWorms.front();
        auto enemyborder = ground->sprite.getPosition().x + ground->getSize().x / 2;
        if (enemyborder < playerborder)
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
    for (auto &Enemy : busyWorms)
        Enemy->updateAnimation(elapsedTime);

    for (auto &Enemy : busyBats)
        Enemy->updateAnimation(elapsedTime);
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