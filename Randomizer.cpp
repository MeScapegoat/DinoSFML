#include "Randomizer.h"

Randomizer::Randomizer() : device(), engine(device()) {}

Randomizer::~Randomizer() {}

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