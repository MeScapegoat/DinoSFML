#pragma once
#include <SFML/Graphics.hpp>

class Model
{
public:
    Model(sf::RenderWindow *);
    virtual ~Model() = default;

public:
    Model(const Model &) = default;
    Model(Model &&) = default;
    Model &operator=(const Model &) = default;
    Model &operator=(Model &&) = default;

public:
    void draw();

    void move(float, float);
    void move(const sf::Vector2f &);

    // setters/getters
public:
    virtual void setSize(float x, float y);
    virtual void setSize(const sf::Vector2f &);
    sf::Vector2f getSize() const;

    virtual void setTexture(const sf::Texture &);

    void setScale(float x, float y);
    void setScale(const sf::Vector2f &);
    sf::Vector2f getScale() const;

    const sf::Vector2f &getPosition() const;

    void setPosition(float, float);
    void setPosition(const sf::Vector2f &);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

    sf::RenderWindow *getWindowHandler() const;

protected:
    sf::Vector2f size{1, 1};        // желанный размер модели
    sf::Vector2f normalScale{1, 1}; // как изменить размер текстуры чтобы соответствовать желанному
    sf::Sprite sprite;
    sf::RenderWindow *windowHandler;
};