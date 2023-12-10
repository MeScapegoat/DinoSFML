#pragma once
#include "Model.h"

#include <deque>

class Enemies
{
public:
    Enemies(sf::Vector2u windowSize, sf::Vector2f playerSize);
    ~Enemies();

public:
    void draw(sf::RenderWindow &) const;
    void move(const sf::Vector2f &);

    void spawn(int, unsigned);

public:
    float getGroundDistance() const;
    float getFlyingDistance() const;

private:
    sf::Vector2u windowSize;
    sf::Vector2f playerSize;

    int groundEnemiesAmount;
    sf::Vector2f groundEnemySize;
    sf::Color groundEnemyColor;
    float distBetweenGroundEnemies;
    std::vector<Model> groundEnemies;
    std::deque<Model *> availableGroundEnemies;
    std::deque<Model *> BusyGroundEnemies;

    int flyingEnemiesAmount;
    sf::Vector2f flyingEnemySize;
    sf::Color flyingEnemyColor;
    float distBetweenFlyingEnemies;
    std::vector<Model> flyingEnemies;
    std::deque<Model *> availableFlyingEnemies;
    std::deque<Model *> BusyFlyingEnemies;
};
