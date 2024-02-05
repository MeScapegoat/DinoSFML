#pragma once
#include <SFML/Graphics.hpp>

class InfoText
{
public:
    InfoText(sf::RenderWindow *);
    InfoText() = default;
    ~InfoText() = default;

public:
    InfoText(const InfoText &) = delete;
    InfoText(InfoText &&) = delete;
    InfoText &operator=(const InfoText &) = delete;
    InfoText &operator=(InfoText &&) = delete;

public:
    void update();

    void draw();

    // setters/getters
public:
    void setPosition(float, float);
    void setPosition(const sf::Vector2f &);

    void setTitleText(const sf::String &text);
    void setContentText(const sf::String &text);

    void setGeneralFont(const sf::Font &);

    sf::RenderWindow *getWindowHandler() const;

    sf::RectangleShape &getBackground();
    sf::Text &getTitle();
    sf::Text &getContent();

    void setActive(bool);
    bool getActive() const;

private:
    sf::RenderWindow *windowHandler{nullptr};
    sf::RectangleShape background; // фон
    sf::Text title;                // заголовок
    sf::Text content;              // содержательный текст

    bool isActive{false}; // Отображать класс на экране или нет
};