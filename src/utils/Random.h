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

        int getInt(int low, int high);
        float getFloat(float low, float high);
        void setupStatic();
};
