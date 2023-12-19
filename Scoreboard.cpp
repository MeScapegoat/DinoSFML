#include "Scoreboard.hpp"

#include <iostream>

Scoreboard::Scoreboard(std::string file)
{
    font.loadFromFile(file);
    setFont(font);
    setScore(0);
}

Scoreboard::~Scoreboard() {}

void Scoreboard::draw(sf::RenderWindow &window) const
{
    window.draw(*this);
}

void Scoreboard::setScore(unsigned newscore)
{
    score = newscore;
    setString("score: " + std::to_string(score));
}

unsigned Scoreboard::getScore() const
{
    return score;
}