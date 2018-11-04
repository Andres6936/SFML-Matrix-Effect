#pragma once 

#include "Symbol.h"
#include <SFML/Graphics.hpp>

class MatrixLine
{
    private:
         // sf::Font It should be a reference but had an error with the "=" operator and got away with the quick and dirty method
        sf::Font m_font; 
        float m_row;
        float m_y{0};
        float m_offset{0};
        float m_step;
        Symbol *m_symbols;
        int m_symbols_size;

        void create_line(int size, int offset);
        void purge_symbols();

    public:
        static int s_char_pos_offset;
        static int s_char_size;
        static int s_HEIGHT;

        MatrixLine();
        MatrixLine(int x, sf::Font& font);

        static void setHeight(int height);
        static void set_char_size(int s);

        void update_draw(sf::RenderWindow& window);
};