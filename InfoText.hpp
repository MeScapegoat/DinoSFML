#pragma once
#include <SFML/Graphics.hpp>

class InfoText
{
public:
    InfoText(sf::RenderWindow *);
    InfoText() = default;
    ~InfoText() = default;

public:
    void update();

    void draw();
    void setPosition(float, float);
    void setPosition(const sf::Vector2f &);

    void setTitleText(const sf::String &text);
    void setContentText(const sf::String &text);

    void setGeneralFont(const sf::Font &);

    void setWindowHandler(sf::RenderWindow *);
    sf::RenderWindow *getWindowHandler();

private:
    sf::RenderWindow *windowHandler{nullptr};

public:
    sf::RectangleShape background; // фон
    sf::Text title;                // заголовок
    sf::Text content;              // содержательный текст

    bool isActive{false}; // Отображать класс на экране или нет
};