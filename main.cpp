#include <SFML/Graphics.hpp>

#include <iostream>
#include <deque>
#include <random>

constexpr int WindowX = 640 * 3;
constexpr int WindowY = 480 * 2;

uint8_t random255()
{
    static std::random_device device;
    static std::mt19937 gen(device());
    static std::uniform_int_distribution<uint8_t> distrb(0, 255);
    return distrb(gen);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(WindowX, WindowY), "First window!");

    sf::RectangleShape rectangle(sf::Vector2f(32.0f, 32.0f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(WindowX / 2, WindowY / 2);
    rectangle.setOrigin(16.0f, 16.0f);

    sf::Color trailColor(sf::Color::White);
    sf::RectangleShape trail(rectangle.getSize());
    trail.setOrigin(trail.getSize().x / 2, trail.getSize().y / 2);
    trail.setFillColor(trailColor);

    std::deque<sf::RectangleShape> trails;
    int x = 1;
    constexpr int mult = 100;
    const float decX = rectangle.getSize().x / (255 * mult);
    const float decY = rectangle.getSize().y / (255 * mult);
    sf::Vector2f velocity(0.2f * mult, 0.2f * mult);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if ((velocity.x > 0 and (rectangle.getPosition().x + rectangle.getSize().x / 2) > WindowX) or
            (velocity.x < 0 and (rectangle.getPosition().x - rectangle.getSize().x / 2) < 0))
            velocity.x = -velocity.x;

        if ((velocity.y > 0 and (rectangle.getPosition().y + rectangle.getSize().y / 2) > WindowY) or
            (velocity.y < 0 and (rectangle.getPosition().y - rectangle.getSize().y / 2) < 0))
            velocity.y = -velocity.y;

        trail.setPosition(rectangle.getPosition());

        window.clear(sf::Color::Black);
        for (auto start = trails.begin(); start != trails.end(); ++start)
        {
            auto size = start->getSize();
            size.x -= decX;
            size.y -= decY;
            start->setSize(size);
            auto color = start->getFillColor();
            if (!x)
                color.a -= 1;
            if (color.a)
            {
                start->setFillColor(color);
                window.draw(*start);
            }
            else
                trails.erase(start);
        }
        // trailColor.r = random255();
        // trailColor.g = random255();
        // trailColor.b = random255();
        trail.setFillColor(trailColor);
        trails.push_back(trail);
        window.draw(trail);
        rectangle.setPosition(rectangle.getPosition() + velocity);
        window.draw(rectangle);
        window.display();
        x = (x + 1) % mult;
    }
}