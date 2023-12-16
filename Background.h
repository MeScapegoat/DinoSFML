#pragma once
#include "Model.h"
#include <vector>

class Background
{
public:
    Background(const sf::Vector2u &windowSize);
    ~Background();

public:
    Background(const Background &) = delete;
    Background(Background &&) = delete;

public:
    Background &operator=(const Background &) = delete;
    Background &operator=(Background &&) = delete;

public:
    void init();

    void draw(sf::RenderWindow &) const;
    void move(const sf::Vector2f &);

    void setGroundHeight(float);
    float getGroundHeight() const;

    void setRoadSize(const sf::Vector2f &);
    const sf::Vector2f &getRoadSize() const;

    void setCloudsAmount(int);
    int getCloudsAmount() const;
    void setCloudSize(const sf::Vector2f &);
    const sf::Vector2f &getCloudSize() const;

    void setTreesAmount(int);
    int getTreesAmount() const;
    void setTreeSize(const sf::Vector2f &);
    const sf::Vector2f &getTreeSize() const;

private:
    sf::Vector2u windowSize;

    float groundHeight; // How far is the "ground", on which the player running
    sf::Vector2f roadSize;
    Model road{roadSize};

    int cloudsAmount;
    sf::Vector2f cloudSize;
    sf::Vector2f distBetweenClouds;
    sf::Vector2f nextCloudPosition;
    std::vector<Model> clouds;

    int treesAmount;
    sf::Vector2f treeSize;
    sf::Vector2f distBetweenTrees;
    sf::Vector2f nextTreePosition;
    std::vector<Model> trees;
};