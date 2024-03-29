// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Background.hpp"

#include <iostream>

Background::Background(sf::RenderWindow *windowH) : windowHandler(windowH)
{
    auto size = windowHandler->getSize(); // размер окна

    setCloudsAmount(3);                                              // кол-во облаков
    setCloudSize(sf::Vector2f(size.x * 0.2f, size.y * 0.15f));       // размер облаков
    distBetweenClouds.x = static_cast<float>(size.x) / cloudsAmount; // расстояние между облаками по х
    distBetweenClouds.y = size.y * 0.1f;                             // расстояние между облаками по у
    cloudTexture.loadFromFile("../Textures/cloud.png");              // Текстура облака

    setTreesAmount(5);                                             // кол-во деревьев
    setTreeSize(sf::Vector2f(size.x * 0.2f, size.y * 0.55f));      // размер деревьев
    distBetweenTrees.x = static_cast<float>(size.x) / treesAmount; // расстояние между деревьями
    treeTexture.loadFromFile("../Textures/tree.png");              // Текстура дерева

    road.setSize(sf::Vector2f(size.x, size.y * 0.1f));      // размер дороги
    road.setFillColor(sf::Color(255, 218, 236));            // цвет дороги
    road.setOrigin(road.getSize().x / 2, road.getSize().y); // центр дороги
    road.setPosition(size.x / 2, size.y);                   // расположение дороги
}

void Background::restart()
{
    auto windowSize = windowHandler->getSize();

    trees.clear();
    trees.reserve(treesAmount + 1);
    nextTreePosition = sf::Vector2f(treeSize.x / 2, getGround() - treeSize.y / 2);
    for (auto n = 0; n < treesAmount + 1; ++n)
    {
        Model tree(windowHandler);
        tree.setTexture(treeTexture);
        tree.setSize(treeSize);
        tree.setPosition(nextTreePosition);
        nextTreePosition += distBetweenTrees;
        trees.push_back(std::move(tree));
    }

    clouds.clear();
    clouds.reserve(cloudsAmount + 1);
    if (distBetweenClouds.y < 0)
        distBetweenClouds.y *= -1;
    nextCloudPosition = sf::Vector2f(cloudSize.x / 2,
                                     nextTreePosition.y - treeSize.y / 2 - cloudSize.y / 2 - distBetweenClouds.y * 1.5f);
    for (auto n = 0; n < cloudsAmount + 1; ++n)
    {
        Model cloud(windowHandler);
        cloud.setTexture(cloudTexture);
        cloud.setSize(cloudSize);
        cloud.setPosition(nextCloudPosition);
        nextCloudPosition += distBetweenClouds;
        distBetweenClouds.y *= -1;
        clouds.push_back(std::move(cloud));
    }
}

void Background::draw()
{
    if (!windowHandler)
        return;

    windowHandler->clear(sf::Color(120, 210, 255)); // цвет фона

    for (auto &cloud : clouds)
        cloud.draw();

    for (auto &tree : trees)
        tree.draw();

    windowHandler->draw(road);
}

void Background::move(float x, float y)
{
    move({x, y});
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

void Background::setCloudsAmount(int amount)
{
    cloudsAmount = amount;
}

int Background::getCloudsAmount() const
{
    return cloudsAmount;
}

void Background::setCloudSize(float x, float y)
{
    cloudSize = {x, y};
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

void Background::setTreeSize(float x, float y)
{
    treeSize = {x, y};
}

void Background::setTreeSize(const sf::Vector2f &size)
{
    treeSize = size;
}

const sf::Vector2f &Background::getTreeSize() const
{
    return treeSize;
}

float Background::getGround() const
{
    return road.getPosition().y - road.getSize().y;
}

void Background::loadCloudTexture(const sf::String &file)
{
    cloudTexture.loadFromFile(file);
}

void Background::loadTreeTexture(const sf::String &file)
{
    treeTexture.loadFromFile(file);
}

sf::RenderWindow *Background::getWindowHandler() const
{
    return windowHandler;
}