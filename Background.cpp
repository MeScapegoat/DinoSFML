// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Background.hpp"

#include <iostream>

Background::Background(sf::RenderWindow *windowH) : windowHandler(windowH)
{
    auto size = windowHandler->getSize(); // размер окна

    setCloudsAmount(3);                                        // кол-во облаков
    setCloudSize(sf::Vector2f(size.x * 0.2f, size.y * 0.15f)); // размер облаков
    setTreesAmount(5);                                         // кол-во деревьев
    setTreeSize(sf::Vector2f(size.x * 0.18f, size.y * 0.55f)); // размер деревьев

    cloudTexture.loadFromFile("../Textures/cloud.png"); // Текстура облака
    treeTexture.loadFromFile("../Textures/tree.png");   // Текстура дерева

    road.setSize(sf::Vector2f(size.x, size.y * 0.1f));
    road.setFillColor(sf::Color(255, 218, 236));

    road.setOrigin(road.getSize().x / 2, road.getSize().y);
    road.setPosition(size.x / 2, size.y);
}

void Background::init()
{
    auto windowSize = windowHandler->getSize();

    trees.clear();
    trees.reserve(treesAmount + 1);
    distBetweenTrees.x = static_cast<float>(windowSize.x) / treesAmount;
    nextTreePosition = sf::Vector2f(treeSize.x / 2, getGround() - treeSize.y / 2);
    for (auto n = 0; n < treesAmount + 1; ++n)
    {
        Model tree(windowHandler);
        tree.setTexture(treeTexture);
        tree.setSize(treeSize);
        tree.sprite.setPosition(nextTreePosition);
        nextTreePosition += distBetweenTrees;
        trees.push_back(std::move(tree));
    }

    clouds.clear();
    clouds.reserve(cloudsAmount + 1);
    distBetweenClouds.x = static_cast<float>(windowSize.x) / cloudsAmount;
    distBetweenClouds.y = windowSize.y * 0.1f;
    nextCloudPosition = sf::Vector2f(cloudSize.x / 2, trees[0].sprite.getPosition().y - trees[0].getSize().y / 2 - cloudSize.y / 2 - distBetweenClouds.y * 1.5f);
    for (auto n = 0; n < cloudsAmount + 1; ++n)
    {
        Model cloud(windowHandler);
        cloud.setTexture(cloudTexture);
        cloud.setSize(cloudSize);
        cloud.sprite.setPosition(nextCloudPosition);
        nextCloudPosition += distBetweenClouds;
        distBetweenClouds.y *= -1;
        clouds.push_back(std::move(cloud));
    }
}

void Background::draw()
{
    windowHandler->clear(sf::Color(120, 210, 255));
    if (!windowHandler)
        return;
    for (auto &cloud : clouds)
        cloud.draw();

    for (auto &tree : trees)
        tree.draw();

    windowHandler->draw(road);
}

void Background::move(float x, float y)
{
    sf::Vector2f offset(x, y);
    nextCloudPosition += offset;
    nextTreePosition += offset;
    for (auto &cloud : clouds)
    {
        if (cloud.sprite.getPosition().x + cloud.getSize().x / 2 > 0)
            cloud.sprite.move(offset);
        else
        {
            cloud.sprite.setPosition(nextCloudPosition);
            nextCloudPosition += distBetweenClouds;
            distBetweenClouds.y *= -1;
        }
    }

    for (auto &tree : trees)
    {
        if (tree.sprite.getPosition().x + tree.getSize().x / 2 > 0)
            tree.sprite.move(offset);
        else
        {
            tree.sprite.setPosition(nextTreePosition);
            nextTreePosition += distBetweenTrees;
        }
    }
}

void Background::move(const sf::Vector2f &offset)
{
    move(offset.x, offset.y);
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

void Background::setWindowHandler(sf::RenderWindow *windowH)
{
    windowHandler = windowH;
    // обработать все модели размеры и прочее в соответствии с новым окном
}

sf::RenderWindow *Background::getWindowHandler()
{
    return windowHandler;
}