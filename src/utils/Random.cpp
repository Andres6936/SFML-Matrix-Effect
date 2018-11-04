#include "Random.h"

#include <ctime>

Random Random::s_Ran;

Random& Random::get()
{
    return Random::s_Ran;
}

void Random::init()
{
    Random r;
    r.setupStatic();
}

Random::Random()
{
    m_engine.seed((unsigned) std::time(nullptr));
}

int Random::getInt(int low, int high)
{
    std::uniform_int_distribution<int> dist(low, high);
    return dist(m_engine);
}

float Random::getFloat(float low, float high)
{
    std::uniform_real_distribution<float> dist(low, high);
    return dist(m_engine);
}

void Random::setupStatic()
{
    Random::s_Ran = Random();
}