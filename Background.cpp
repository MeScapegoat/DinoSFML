#include "Background.h"

Background::Background(const sf::Vector2u &windowSize, int cloudsAmount, int treesAmount)
    : windowSize(windowSize), ground(windowSize.y * 0.7f),
      cloudsAmount(cloudsAmount), treesAmount(treesAmount),
      road(sf::Vector2f(windowSize.x, 10))
{
    clouds.reserve(cloudsAmount);
    auto position = sf::Vector2f(windowSize.x * 0.1f, windowSize.y * 0.8f);
    auto offset = sf::Vector2f(windowSize.x * 0.1f, 0);
    for (auto n = 0; n < cloudsAmount; ++n)
    {
        Model cloud(sf::Vector2f(20, 20));
        cloud.setColor(sf::Color::Blue);
        cloud.setPosition(position);
        position += offset;
        clouds.push_back(cloud);
    }

    trees.reserve(cloudsAmount);
    position = sf::Vector2f(windowSize.x * 0.1f, ground);
    offset = sf::Vector2f(windowSize.x * 0.1f, 0);
    for (auto n = 0; n < treesAmount; ++n)
    {
        Model tree(sf::Vector2f(20, 40));
        tree.setColor(sf::Color(165, 42, 42));
        tree.setPosition(position);
        position += offset;
        trees.push_back(tree);
    }
    road.setPosition(sf::Vector2f(windowSize.x / 2, ground));
}

Background::~Background() {}

void Background::draw(sf::RenderWindow &window)
{
    for (const auto &cloud : clouds)
        cloud.draw(window);
    for (const auto &tree : trees)
        tree.draw(window);
    road.draw(window);
}

void Background::update(const sf::Vector2f &velocity)
{
}

void Background::setGround(int newground)
{
    ground = newground;
}

int Background::getGround()
{
    return ground;
}

void Background::move(const sf::Vector2f &offset)
{
    for (auto &cloud : clouds)
    {
        if (cloud.getPosition().x + cloud.getSize().x / 2 + offset.x > 0)
            cloud.move(offset);
        else
            cloud.setPosition(sf::Vector2f(cloud.getSize().x + windowSize.x, cloud.getPosition().y));
    }

    for (auto &tree : trees)
    {
        if (tree.getPosition().x + tree.getSize().x / 2 + offset.x > 0)
            tree.move(offset);
        else
            tree.setPosition(sf::Vector2f(tree.getSize().x + windowSize.x, tree.getPosition().y));
    }
}