// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Randomizer.hpp"

Randomizer::Randomizer() : device(), engine(device()) {}

int Randomizer::getInt(int min, int max)
{
    std::uniform_int_distribution<int> dis(min, max);
    return dis(engine);
}

float Randomizer::getFloat(float min, float max)
{
    std::uniform_real_distribution<float> dis(min, max);
    return dis(engine);
}