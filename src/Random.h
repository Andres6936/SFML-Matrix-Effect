#pragma once

#include <random>

class Random
{
    private:
        std::mt19937 m_engine;
        static Random s_Ran;
        
    public:
        Random();
        static Random& get();
        static void init();

        int getInt(int low, int high)
        {
            std::uniform_int_distribution<int> dist(low, high);
            return dist(m_engine);
        }
	
        float getFloat(float low, float high)
        {
            std::uniform_real_distribution<float> dist(low, high);
            return dist(m_engine);
        }
	
        void setupStatic();
};
