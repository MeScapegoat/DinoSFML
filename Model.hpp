#pragma once
#include <SFML/Graphics.hpp>

class Model
{
public:
    Model(sf::RenderWindow *);
    virtual ~Model() = default;

public:
    void draw();

    virtual void setSize(float x, float y);
    virtual void setSize(const sf::Vector2f &);
    sf::Vector2f getSize() const;

    virtual void setTexture(const sf::Texture &);

    void setScale(float x, float y);
    void setScale(const sf::Vector2f &);

    sf::Vector2f getScale() const;

protected:
    sf::Vector2f size{1, 1};        // желанный размер модели
    sf::Vector2f normalScale{1, 1}; // как изменить размер текстуры чтобы соответствовать желанному

public:
    sf::Sprite sprite;
    sf::RenderWindow *windowHandler;
};