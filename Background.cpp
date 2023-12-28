// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Background.hpp"

#include <iostream>

Background::Background(const sf::Vector2u &windowSize) : windowSize(windowSize) {}

Background::~Background() {}

void Background::init()
{
    road.setSize(roadSize);
    road.setOrigin(roadSize.x / 2, roadSize.y / 2);
    road.setPosition(windowSize.x / 2, groundHeight);

    clouds.clear();
    clouds.reserve(cloudsAmount + 1);
    distBetweenClouds.x = static_cast<float>(windowSize.x) / cloudsAmount;
    distBetweenClouds.y = windowSize.y * 0.1f;
    nextCloudPosition = sf::Vector2f(cloudSize.x / 2, windowSize.y * 0.2f);
    for (auto n = 0; n < cloudsAmount + 1; ++n)
    {
        Model cloud;
        cloud.setTexture(cloudTexture);
        cloud.setSize(cloudSize);
        cloud.setPosition(nextCloudPosition);
        nextCloudPosition += distBetweenClouds;
        distBetweenClouds.y *= -1;
        clouds.push_back(std::move(cloud));
    }

    trees.clear();
    trees.reserve(treesAmount + 1);
    distBetweenTrees.x = static_cast<float>(windowSize.x) / treesAmount;
    nextTreePosition = sf::Vector2f(treeSize.x / 2, groundHeight - treeSize.y / 2);
    for (auto n = 0; n < treesAmount + 1; ++n)
    {
        Model tree;
        tree.setTexture(treeTexture);
        tree.setSize(treeSize);
        tree.setPosition(nextTreePosition);
        nextTreePosition += distBetweenTrees;
        trees.push_back(std::move(tree));
    }
}

void Background::draw(sf::RenderWindow &window) const
{
    for (const auto &cloud : clouds)
        cloud.draw(window);

    for (const auto &tree : trees)
        tree.draw(window);

    window.draw(road);
}

void Background::move(const sf::Vector2f &offset)
{
    nextCloudPosition += offset;
    nextTreePosition += offset;
    for (auto &cloud : clouds)
    {
        if (cloud.getPosition().x + cloud.getSize().x / 2 > 0)
            cloud.move(offset);
        else
        {
            cloud.setPosition(nextCloudPosition);
            nextCloudPosition += distBetweenClouds;
            distBetweenClouds.y *= -1;
        }
    }

    for (auto &tree : trees)
    {
        if (tree.getPosition().x + tree.getSize().x / 2 > 0)
            tree.move(offset);
        else
        {
            tree.setPosition(nextTreePosition);
            nextTreePosition += distBetweenTrees;
        }
    }
}

void Background::setGroundHeight(float newground)
{
    groundHeight = newground;
}

float Background::getGroundHeight() const
{
    return groundHeight - roadSize.y / 2;
}

void Background::setRoadSize(const sf::Vector2f &size)
{
    roadSize = size;
}

const sf::Vector2f &Background::getRoadSize() const
{
    return roadSize;
}

void Background::setCloudsAmount(int amount)
{
    cloudsAmount = amount;
}

int Background::getCloudsAmount() const
{
    return cloudsAmount;
}

void Background::setCloudSize(const sf::Vector2f &size)
{
    cloudSize = size;
}

const sf::Vector2f &Background::getCloudSize() const
{
    return cloudSize;
}

void Background::setTreesAmount(int amount)
{
    treesAmount = amount;
}

int Background::getTreesAmount() const
{
    return treesAmount;
}

void Background::setTreeSize(const sf::Vector2f &size)
{
    treeSize = size;
}

const sf::Vector2f &Background::getTreeSize() const
{
    return treeSize;
}

void Background::loadCloudTexture(const sf::String &file)
{
    cloudTexture.loadFromFile(file);
}

void Background::loadTreeTexture(const sf::String &file)
{
    treeTexture.loadFromFile(file);
}