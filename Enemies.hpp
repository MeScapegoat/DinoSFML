#pragma once
#include <vector>
#include <deque>

#include "AnimatedModel.hpp"
#include "Player.hpp"
#include "Randomizer.hpp"

class Enemies
{
public:
    Enemies(sf::RenderWindow *, Player *);
    ~Enemies() = default;

public:
    Enemies(const Enemies &) = delete;
    Enemies(Enemies &&) = delete;
    Enemies &operator=(const Enemies &) = delete;
    Enemies &operator=(Enemies &&) = delete;

public:
    void restart();

    void draw();

    void move(float, float);
    void move(const sf::Vector2f &);

    bool spawn(float);

    void loadBatTexture(const sf::String &);
    void loadWormTexture(const sf::String &);

    bool checkCrash() const;
    bool checkOvercome();

    void updateAnimations(float);

    // setters/getters
public:
    sf::RenderWindow *getWindowHandler();

    float getBetweenDistance() const;

    void setPlayerHandler(Player *);
    Player *getPlayerHandler();

    void setGroundHeight(float);
    float getGroundHeight() const;

    void setSpawnTimer(float);
    float getSpawnTimer() const;

    void setMinSpawnInterval(float);
    float getMinSpawnInterval() const;

    void setSpawnInterval(float);
    float getSpawnInterval() const;

    const sf::Vector2f &getWormSize() const;
    const sf::Vector2f &getBatSize() const;

private:
    sf::RenderWindow *windowHandler;
    Player *playerHandler;

    float groundHeight{0};    // уровень "земли"
    float distBetweenEnemies; // расстояние между мобами

    AnimationInfo wormAnim;                     // анимация червей
    sf::Texture wormTexture;                    // текстура червей
    unsigned int wormsAmount{0};                // кол-во червей
    sf::Vector2f wormSize;                      // размер червей
    std::vector<AnimatedModel> worms;           // все черви
    std::deque<AnimatedModel *> availableWorms; // черви готовые к спавну
    std::deque<AnimatedModel *> busyWorms;      // черви на экране
    std::deque<AnimatedModel *> uncheckedWorms; // Костыль для счетчика очков: не просмотренные черви

    AnimationInfo batAnim;                     // анимация мышей
    sf::Texture batTexture;                    // текстура мышей
    unsigned int batsAmount{0};                // кол-во мышей
    sf::Vector2f batSize;                      // размер мышей
    std::vector<AnimatedModel> bats;           // всего мышей
    std::deque<AnimatedModel *> availableBats; // мыши готовые к спавну
    std::deque<AnimatedModel *> busyBats;      // мыши на экране
    std::deque<AnimatedModel *> uncheckedBats; // Костыль для счетчика очков: не просмотренные мыши

    float spawnTimer{0};       // таймер спавнера
    float minSpawnInterval{0}; // минимальный интервал спавна
    float spawnInterval{0};    // текущий интервал спавна (не меньше минимального)

    Randomizer random;
};
