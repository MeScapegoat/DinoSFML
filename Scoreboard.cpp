// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Scoreboard.hpp"

Scoreboard::Scoreboard()
{
    setFillColor(sf::Color::Red);
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