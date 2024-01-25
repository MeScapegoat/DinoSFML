// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "InfoText.hpp"

InfoText::InfoText(sf::RenderWindow *windowH) : windowHandler(windowH)
{
    title.setCharacterSize(windowH->getSize().y * 0.1f);
    content.setCharacterSize(windowH->getSize().y * 0.1f);
    update();
    title.setFillColor(sf::Color::Red);
    content.setFillColor(sf::Color::Red);
    content.setOutlineColor(sf::Color::Cyan);
    content.setOutlineThickness(1.f);
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
    content.setPosition(x, title.getPosition().y + 3.f * title.getCharacterSize());
}

void InfoText::setPosition(const sf::Vector2f &pos)
{
    setPosition(pos.x, pos.y);
}

void InfoText::setTitleText(const sf::String &text)
{
    title.setString(text);
    auto titleLocal = title.getLocalBounds();
    title.setOrigin(titleLocal.width / 2, titleLocal.height / 2);

    // Венец гениальности и глупости:
    // Вычисляем необходимый размер шрифта чтобы влезть в рамки
    // Дорого.
    auto titleGlobal = title.getGlobalBounds();
    auto backgroundGlobal = background.getGlobalBounds();
    while (titleGlobal.left < backgroundGlobal.left * 0.9f or
           (titleGlobal.left + titleGlobal.width > backgroundGlobal.left * 0.9f + backgroundGlobal.width * 0.9f))
    {
        title.setCharacterSize(title.getCharacterSize() * 0.9f);
        titleLocal = title.getLocalBounds();
        title.setOrigin(titleLocal.width / 2, titleLocal.height / 2);
        titleGlobal = title.getGlobalBounds();
        backgroundGlobal = background.getGlobalBounds();
    }
}

void InfoText::setContentText(const sf::String &text)
{
    content.setString(text);
    auto contentLocal = content.getLocalBounds();
    content.setOrigin(contentLocal.width / 2, contentLocal.height / 2);

    // Венец гениальности и глупости:
    // Вычисляем необходимый размер шрифта чтобы влезть в рамки
    // Дорого.
    auto contentGlobal = content.getGlobalBounds();
    auto backgroundGlobal = background.getGlobalBounds();
    while (contentGlobal.left < backgroundGlobal.left * 0.9f or
           (contentGlobal.left + contentGlobal.width > backgroundGlobal.left * 0.9f + backgroundGlobal.width * 0.9f))
    {
        content.setCharacterSize(content.getCharacterSize() * 0.9f);
        contentLocal = content.getLocalBounds();
        content.setOrigin(contentLocal.width / 2, contentLocal.height / 2);
        contentGlobal = content.getGlobalBounds();
        backgroundGlobal = background.getGlobalBounds();
    }
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