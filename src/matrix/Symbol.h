#pragma once

#include <SFML/Graphics.hpp>

class Symbol
{
    private:
        sf::Text m_text;
        float m_step;
        float m_x;
        float m_y;
        sf::Color m_clr;
        bool m_isfirst;
        float m_duration;
        float m_current_timestamp{0};
        static sf::Color s_clr;
        static sf::Color s_first_clr;

    public:
        static int s_size;
        
        Symbol();
        Symbol(sf::Font& font, float x, float offset_y, float duration, bool isfirst);

        void newchar();

        void update_clr();

        void update(float step);

        void draw(sf::RenderWindow& window);
};