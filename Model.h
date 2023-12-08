#include <SFML/Graphics.hpp>
class Model
{
public:
    Model(const sf::Vector2f &size);
    ~Model();

public:
    void draw(sf::RenderWindow &) const;
    void move(const sf::Vector2f &);
    void setPosition(const sf::Vector2f &);
    const sf::Vector2f &getPosition() const;
    void setColor(const sf::Color &);
    const sf::Vector2f &getSize() const;

private:
    sf::RectangleShape rect;
};