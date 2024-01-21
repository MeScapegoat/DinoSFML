#pragma once

#include <vector>

#include "Model.hpp"

extern sf::Vector2i TEXTURE_SIZE;

// TextureSheet - сетка текстур (см. /Textures/)

// Информация об анимации
struct AnimationInfo
{
public:
    AnimationInfo() = default;
    AnimationInfo(const sf::Vector2i &s, int f, float i) : start(s), frames(f), interval(i) {}

public:
    AnimationInfo(const AnimationInfo &) = default;
    AnimationInfo &operator=(const AnimationInfo &) = default;

public:
    sf::Vector2i start; // Начальные координаты текстуры в TextureSheet
    int frames;         // Всего кадров в анимации
    float interval;     // Интервал между кадрами

    sf::Vector2i currentTexture{start}; // Текущая позиция в TextureSheet
    int currentFrame{0};                // Текущий кадр, начиная с 0
    float timer{0.f};                   // Таймер анимации
};

class AnimatedModel : public Model
{
public:
    AnimatedModel(sf::RenderWindow *);
    ~AnimatedModel() = default;

public:
    void setCurrentAnimation(const AnimationInfo &);
    const AnimationInfo &getCurrentAnimation() const;

    void updateAnimation(float);

    void setSize(float x, float y) override;
    void setSize(const sf::Vector2f &) override;

    void setTexture(const sf::Texture &) override;

private:
    AnimationInfo currentAnimation;
};