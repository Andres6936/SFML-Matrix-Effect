#include "Random.h"

#include <ctime>

Random Random::s_Ran;

Random& Random::get()
{
    return s_Ran;
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

void Random::setupStatic()
{
    Random::s_Ran = Random();
}