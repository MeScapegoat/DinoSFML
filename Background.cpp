#include "Background.h"

Background::Background(const sf::Vector2u &windowSize) : windowSize(windowSize) {}

Background::~Background() {}

void Background::init()
{
    clouds.clear();
    clouds.reserve(cloudsAmount);
    auto position = sf::Vector2f(cloudSize.x / 2, windowSize.y * 0.2f);
    auto offset = sf::Vector2f(windowSize.x / (cloudsAmount - 1), windowSize.y * 0.1f);
    for (auto n = 0; n < cloudsAmount; ++n)
    {
        Model cloud(cloudSize);
        cloud.setColor(sf::Color::Blue);
        cloud.setPosition(position);
        offset.y *= -1;
        position += offset;
        clouds.push_back(std::move(cloud));
    }

    trees.clear();
    trees.reserve(treesAmount);
    position = sf::Vector2f(treeSize.x / 2, groundHeight - treeSize.y / 2);
    offset = sf::Vector2f(windowSize.x / (treesAmount - 1), 0);
    for (auto n = 0; n < treesAmount; ++n)
    {
        Model tree(treeSize);
        tree.setColor(sf::Color(150, 75, 0));
        tree.setPosition(position);
        position += offset;
        trees.push_back(std::move(tree));
    }

    road.setPosition(sf::Vector2f(windowSize.x / 2, groundHeight));
}

void Background::draw(sf::RenderWindow &window)
{
    for (const auto &cloud : clouds)
        cloud.draw(window);
    for (const auto &tree : trees)
        tree.draw(window);
    road.draw(window);
}

void Background::update(const sf::Vector2f &velocity) {}

void Background::move(const sf::Vector2f &offset)
{
    for (auto &cloud : clouds)
    {
        if (cloud.getPosition().x + cloud.getSize().x / 2 + offset.x > 0)
            cloud.move(offset);
        else
            cloud.setPosition(sf::Vector2f(windowSize.x - cloud.getSize().x / 2 + (windowSize.x / (cloudsAmount - 1)), cloud.getPosition().y));
    }

    for (auto &tree : trees)
    {
        if (tree.getPosition().x + tree.getSize().x / 2 + offset.x > 0)
            tree.move(offset);
        else
            tree.setPosition(sf::Vector2f(windowSize.x - tree.getSize().x / 2 + windowSize.x / (treesAmount - 1), tree.getPosition().y));
    }
}

void Background::setGroundHeight(float newground)
{
    groundHeight = newground;
}

float Background::getGroundHeight()
{
    return groundHeight;
}

void Background::setRoadSize(sf::Vector2f size)
{
    roadSize = std::move(size);
}

const sf::Vector2f &Background::getRoadSize() const
{
    return roadSize;
}

void Background::setCloudsAmount(int amount)
{
    cloudsAmount = amount;
}

int Background::getCloudsAmount()
{
    return cloudsAmount;
}

void Background::setCloudSize(sf::Vector2f size)
{
    cloudSize = std::move(size);
}

const sf::Vector2f &Background::getCloudSize() const
{
    return cloudSize;
}

void Background::setTreesAmount(int amount)
{
    treesAmount = amount;
}

int Background::getTreesAmount()
{
    return treesAmount;
}

void Background::setTreeSize(sf::Vector2f size)
{
    treeSize = std::move(size);
}

const sf::Vector2f &Background::getTreeSize() const
{
    return treeSize;
}