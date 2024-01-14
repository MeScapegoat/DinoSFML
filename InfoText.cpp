// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "InfoText.hpp"

InfoText::InfoText(sf::RenderWindow *windowH) : windowHandler(windowH)
{
    update();
}

void InfoText::update()
{
    if (!windowHandler)
        return;
    auto windowSize = windowHandler->getSize();
    background.setSize(sf::Vector2f(windowSize.x * 0.5, windowSize.y * 0.5));
    background.setOutlineColor(sf::Color::Red);
    background.setOutlineThickness(5.f);
    background.setFillColor(sf::Color::Black);
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
    title.setCharacterSize(background.getSize().y * 0.35);
    content.setCharacterSize(background.getSize().y * 0.2);
}

void InfoText::draw()
{
    if (windowHandler and isActive)
    {
        windowHandler->draw(background);
        windowHandler->draw(title);
        windowHandler->draw(content);
    }
}

void InfoText::setPosition(float x, float y)
{
    background.setPosition(x, y);
    title.setPosition(x, y - background.getSize().y * 0.4f);
    content.setPosition(x, title.getPosition().y + 1.5f * title.getCharacterSize());
}

void InfoText::setPosition(const sf::Vector2f &pos)
{
    setPosition(pos.x, pos.y);
}

void InfoText::setTitleText(const sf::String &text)
{
    title.setString(text);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
}

void InfoText::setContentText(const sf::String &text)
{
    content.setString(text);
    content.setOrigin(content.getLocalBounds().width / 2, content.getLocalBounds().height / 2);
}

void InfoText::setGeneralFont(const sf::Font &font)
{
    title.setFont(font);
    content.setFont(font);
}

void InfoText::setWindowHandler(sf::RenderWindow *windowH)
{
    windowHandler = windowH;
    update();
}

sf::RenderWindow *InfoText::getWindowHandler()
{
    return windowHandler;
}