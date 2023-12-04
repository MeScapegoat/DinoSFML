#include <SFML/Graphics.hpp>
#include <deque>

#include <iostream>

struct CUBETRAIL
{
    CUBETRAIL(int WindowX, int WindowY) : rectangle(sf::Vector2f(32.0f, 32.0f)), trailColor(sf::Color::White),
                                          trail(rectangle.getSize()),
                                          decX(rectangle.getSize().x / (255 * cap)),
                                          decY(rectangle.getSize().y / (255 * cap)),
                                          velocity(0.2f * cap, 0.2f * cap)
    {
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(WindowX / 2, WindowY / 2);
        rectangle.setOrigin(16.0f, 16.0f);

        trail.setOrigin(trail.getSize().x / 2, trail.getSize().y / 2);
        trail.setFillColor(trailColor);
    }
    int iteration = 4;
    int cap = 10;
    sf::RectangleShape rectangle;
    sf::Color trailColor;
    sf::RectangleShape trail;
    std::deque<sf::RectangleShape> trails;
    sf::Vector2f velocity;

    const float decX = 0;
    const float decY = 0;
};

class Game
{
public:
    Game(sf::VideoMode mode, const sf::String &title, uint32_t style = sf::Style::Default);
    ~Game();

public:
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;

public:
    void processEvent();
    void update();
    void render();
    void run();

private:
    sf::RenderWindow window;
    sf::Event event;
    // ? background
    // ? player
    // ? enemies
public:
    CUBETRAIL ct;
};