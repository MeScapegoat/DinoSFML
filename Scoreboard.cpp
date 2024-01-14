// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Scoreboard.hpp"

Scoreboard::Scoreboard(sf::RenderWindow *windowH) : windowHandler(windowH)
{
    setScore(0);
}

void Scoreboard::draw()
{
    windowHandler->draw(*this);
}

void Scoreboard::increaseScore(unsigned inc)
{
    setScore(score + inc);
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