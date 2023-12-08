#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy();
    ~Enemy();

public:
    void draw(sf::RenderWindow &);
    void move(const sf::Vector2f &);
    void setPosition(const sf::Vector2f &);

private:
    sf::RectangleShape cube;
};