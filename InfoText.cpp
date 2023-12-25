// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "InfoText.hpp"

InfoText::InfoText(const sf::Vector2u &windowSize)
{
    background.setSize(sf::Vector2f(windowSize.x * 0.5, windowSize.y * 0.5));
    background.setOutlineColor(sf::Color::Red);
    background.setFillColor(sf::Color::Black);
    setTitleCharacterSize(background.getSize().y * 0.35);
    setInfoCharacterSize(background.getSize().y * 0.2);
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
    setPosition(windowSize.x / 2, windowSize.y * 0.1f + background.getSize().y / 2);
}

InfoText::~InfoText() {}

void InfoText::draw(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(title);
    window.draw(info);
}

void InfoText::setFont(const sf::Font &font)
{
    title.setFont(font);
    info.setFont(font);
}

void InfoText::setPosition(float x, float y)
{
    background.setPosition(x, y);
    title.setPosition(x, y - background.getSize().y * 0.4f);
    info.setPosition(x, title.getPosition().y + 1.5f * title.getCharacterSize());
}

void InfoText::setTextColor(const sf::Color &color)
{
    title.setFillColor(color);
    info.setFillColor(color);
}

void InfoText::setBackgroundColor(const sf::Color &color)
{
    background.setFillColor(color);
}

void InfoText::setTitleCharacterSize(unsigned size)
{
    title.setCharacterSize(size);
}

void InfoText::setInfoCharacterSize(unsigned size)
{
    info.setCharacterSize(size);
}

void InfoText::setTitleText(const sf::String &text)
{
    title.setString(text);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
}

void InfoText::setInfoText(const sf::String &text)
{
    info.setString(text);
    info.setOrigin(info.getLocalBounds().width / 2, info.getLocalBounds().height / 2);
}