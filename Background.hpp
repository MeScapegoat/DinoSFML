#pragma once
#include <vector>

#include "Model.hpp"

class Background
{
public:
    Background(sf::RenderWindow *);
    ~Background() = default;

public:
    Background(const Background &) = delete;
    Background(Background &&) = delete;
    Background &operator=(const Background &) = delete;
    Background &operator=(Background &&) = delete;

public:
    void init();

    void draw();

    void move(float, float);
    void move(const sf::Vector2f &);

    void setCloudsAmount(int);
    int getCloudsAmount() const;

    void setCloudSize(float, float);
    void setCloudSize(const sf::Vector2f &);
    const sf::Vector2f &getCloudSize() const;

    void setTreesAmount(int);
    int getTreesAmount() const;

    void setTreeSize(float, float);
    void setTreeSize(const sf::Vector2f &);
    const sf::Vector2f &getTreeSize() const;

    float getGround() const;

    void loadCloudTexture(const sf::String &);
    void loadTreeTexture(const sf::String &);

    // не доработана - не использовать
    void setWindowHandler(sf::RenderWindow *);
    sf::RenderWindow *getWindowHandler();

public:
    sf::RectangleShape road;

private:
    sf::RenderWindow *windowHandler{nullptr};
    sf::Texture cloudTexture;
    int cloudsAmount;
    sf::Vector2f cloudSize;
    sf::Vector2f distBetweenClouds;
    sf::Vector2f nextCloudPosition;
    std::vector<Model> clouds;

    sf::Texture treeTexture;
    int treesAmount;
    sf::Vector2f treeSize;
    sf::Vector2f distBetweenTrees;
    sf::Vector2f nextTreePosition;
    std::vector<Model> trees;
};