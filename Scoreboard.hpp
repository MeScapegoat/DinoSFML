#pragma once
#include <SFML/Graphics.hpp>

class Scoreboard : public sf::Text
{
public:
    Scoreboard(sf::RenderWindow *);
    ~Scoreboard() = default;

public:
    void update();
    void draw();

    void setScore(unsigned);
    void increaseScore(unsigned);
    unsigned getScore() const;

public:
    sf::RenderWindow *windowHandler;

private:
    unsigned score;
};