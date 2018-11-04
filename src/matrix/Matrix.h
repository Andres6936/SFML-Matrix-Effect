#pragma once

#include "MatrixLine.h"
#include <SFML/Graphics.hpp>

class Matrix
{
    private:
        MatrixLine **m_lines;
        int m_line_count;

    public:
        Matrix(int width, int height, sf::Font& font);

        void update_draw(sf::RenderWindow& window);
};