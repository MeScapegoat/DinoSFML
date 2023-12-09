#include <SFML/Graphics.hpp>

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

    void draw(sf::RenderWindow &);
    void update(const sf::Vector2f &);
    void move(const sf::Vector2f &);

    void setGroundHeight(float);
    float getGroundHeight();
    void setRoadSize(sf::Vector2f);
    const sf::Vector2f &getRoadSize() const;

    void setCloudsAmount(int);
    int getCloudsAmount();
    void setCloudSize(sf::Vector2f);
    const sf::Vector2f &getCloudSize() const;

    void setTreesAmount(int);
    int getTreesAmount();
    void setTreeSize(sf::Vector2f);
    const sf::Vector2f &getTreeSize() const;

private:
    sf::Vector2u windowSize;

    float groundHeight{windowSize.y * 0.7f}; // How far is the "ground", on which the player running
    sf::Vector2f roadSize{windowSize.x, windowSize.y * 0.05f};
    Model road{roadSize};

    int cloudsAmount{6};
    sf::Vector2f cloudSize{windowSize.x * 0.08f, windowSize.y * 0.05f};
    std::vector<Model> clouds;

    int treesAmount{12};
    sf::Vector2f treeSize{windowSize.x * 0.04f, windowSize.y * 0.1f};
    std::vector<Model> trees;
};