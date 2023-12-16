#pragma once

#include <random>

class Randomizer
{
public:
    Randomizer();
    ~Randomizer();

public:
    Randomizer(const Randomizer &) = delete;
    Randomizer(Randomizer &&) = delete;
    Randomizer &operator=(const Randomizer &) = delete;
    Randomizer &operator=(Randomizer &&) = delete;

public:
    int getInt(int min, int max);
    float getFloat(float min, float max);

private:
    std::random_device device;
    std::default_random_engine engine;
};