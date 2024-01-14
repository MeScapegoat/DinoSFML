// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>

#include "Game.hpp"

Game::Game(sf::VideoMode mode, const sf::String &title, uint32_t style)
    : window(mode, title, style),
      gameOverText(&window),
      pausedText(&window),
      scoreboard(&window),
      background(&window),
      player("../assets/proto.png"),
      enemies(window.getSize())
{
    const auto &size = window.getSize();

    // Расположение
    scoreboard.setPosition(0, size.y);
    pausedText.setPosition(window.getSize().x / 2, window.getSize().y * 0.4f);
    gameOverText.setPosition(window.getSize().x / 2, window.getSize().y * 0.4f);

    // Внешний вид
    player.setSize(size.x * 0.06f, size.y * 0.2f);

    background.setCloudsAmount(3);                                         // кол-во облаков
    background.setCloudSize(sf::Vector2f(size.x * 0.12f, size.y * 0.08f)); // размер облаков
    background.setTreesAmount(11);                                         // кол-во деревьев
    background.setTreeSize(sf::Vector2f(size.x * 0.06f, size.y * 0.3f));   // размер деревьев
    background.loadCloudTexture("../assets/cloud.png");                    // Текстура облака
    background.loadTreeTexture("../assets/tree.png");                      // Текстура дерева

    enemies.setPlayerSize(player.getSize());
    enemies.loadFlyingEnemiesTextures(std::vector<sf::String>{"../assets/batup.png", "../assets/batdown.png"});
    enemies.loadGroundEnemiesTextures(std::vector<sf::String>{"../assets/wormup.png", "../assets/wormdown.png"});
    enemies.setGroundHeight(background.getGround());
    font.loadFromFile("../LOST_LATE.ttf");

    scoreboard.setFont(font);
    scoreboard.setCharacterSize(size.y - background.road.getPosition().y);
    scoreboard.setOrigin(0, scoreboard.getCharacterSize());
    scoreboard.setFillColor(sf::Color::Red);

    pausedText.setGeneralFont(font);
    pausedText.setTitleText("Game is Paused!");
    pausedText.setContentText("ESC - pause/continue\n"
                              "arrow up/W - jump\n"
                              "arrow down/S - slide");
    pausedText.title.setFillColor(sf::Color::Red);
    pausedText.content.setFillColor(sf::Color::Red);
    // pausedText.content.setOutlineColor(sf::Color::Cyan);
    // pausedText.content.setOutlineThickness(1.f);

    gameOverText.setGeneralFont(font);
    gameOverText.setTitleText("Game over!");
    gameOverText.setContentText("Press ESC to continue");
    gameOverText.title.setFillColor(sf::Color::Red);
    gameOverText.content.setFillColor(sf::Color::Red);

    // Геймплейное
    player.setJumpHeight(size.y * 0.5f);
    isPaused = true;
    pausedText.isActive = true;

    restart();
}

void Game::restart()
{
    const auto &size = window.getSize();
    background.init();
    enemies.init();
    worldVelocity = 200;
    maxWorldVelocity = worldVelocity * 5;
    worldVelocityStep = (maxWorldVelocity - worldVelocity) / 100;
    elapsedTime = 0;

    player.setPosition(size.x * 0.15f + player.getSize().x / 2,
                       background.getGround() - player.getSize().y / 2);
    player.setJumpVelocity(size.y * 0.001f * -1);
    player.setJumpVelocityStep(player.getJumpVelocity() / 100);
    enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
    scoreboard.setScore(0);
}

void Game::render()
{
    if (!window.isOpen())
        return;

    window.clear(sf::Color::Black);

    background.draw();
    scoreboard.draw();
    enemies.draw(window);
    player.draw(window);

    pausedText.draw();
    gameOverText.draw();

    // t.draw();
    window.display();
}

void Game::update()
{
    if (!window.isOpen())
        return;
    elapsedTime = clock.restart().asSeconds();
    //
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                if (isGameOver)
                {
                    restart();
                    isGameOver = !isGameOver;
                    gameOverText.isActive = !gameOverText.isActive;
                    break;
                }
                isPaused = !isPaused;
                pausedText.isActive = !pausedText.isActive;
                break;

            default:
                break;
            } // switch event.key.code

        default:
            break;
        } // switch event.type
    }

    if (isPaused or isGameOver)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (!player.getCurrentJumpVelocity())
        {
            player.setScale(2.f, 0.5f);
            player.setPosition(player.getPosition().x, background.getGround() - player.getSize().y / 2);
        }
    }
    else
    {
        if (!player.getCurrentJumpVelocity())
        {
            player.setScale(1.f, 1.f);
            player.setPosition(player.getPosition().x, background.getGround() - player.getSize().y / 2);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (player.getCurrentJumpVelocity() > 0)
            player.setCurrentJumpVelocity(-1 * player.getJumpVelocity());
        else
            player.setCurrentJumpVelocity(player.getJumpVelocity());
    }
    //

    if (enemies.checkCrash(player))
    {
        // isGameOver = true;
        // gameOverText.toShow = true;
        // return;
    }

    if (enemies.checkOvercome(player))
        scoreboard.increaseScore(1);

    if (enemies.spawn(elapsedTime))
    {
        enemies.setMinSpawnInterval(std::max(enemies.getFlyingDistance(), enemies.getGroundDistance()) / worldVelocity);
        if (worldVelocity < maxWorldVelocity)
        {
            worldVelocity += worldVelocityStep;
            player.setJumpVelocity(player.getJumpVelocity() + player.getJumpVelocityStep());
        }
    }
    enemies.updateAnimations(elapsedTime, worldVelocity);

    if (player.getCurrentJumpVelocity() < 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 < player.getJumpHeight())
            player.setCurrentJumpVelocity(player.getCurrentJumpVelocity() * -1);
    }
    else if (player.getCurrentJumpVelocity() > 0)
    {
        if (player.getPosition().y + player.getSize().y / 2 > background.getGround())
            player.setCurrentJumpVelocity(0);
    }

    auto speed = worldVelocity * elapsedTime * -1.f;
    background.move(sf::Vector2f(speed, 0));
    enemies.move(sf::Vector2f(speed, 0));
    player.move(sf::Vector2f(0, player.getCurrentJumpVelocity()));
}

void Game::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

Game::~Game() {}