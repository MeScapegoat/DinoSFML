#include <SFML/Graphics.hpp>

#include "Model.h"

#include <vector>

class Background
{
public:
    Background(const sf::Vector2u &windowSize, int cloudsAmount, int treesAmount);
    ~Background();

public:
    Background(const Background &) = delete;
    Background(Background &&) = delete;

public:
    Background &operator=(const Background &) = delete;
    Background &operator=(Background &&) = delete;

public:
    void draw(sf::RenderWindow &);
    void update(const sf::Vector2f &);
    void move(const sf::Vector2f &);
    void setGround(int);
    int getGround();

private:
    sf::Vector2u windowSize;
    float ground;
    int cloudsAmount;
    int treesAmount;
    Model road;
    std::vector<Model> clouds;
    std::vector<Model> trees;
};