#include <iostream>
#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "MatrixLine.h"
const int CHAR_SIZE = 18;

Matrix::Matrix(int width, int height, sf::Font& font)
{
    MatrixLine::setHeight(height);
    MatrixLine::set_char_size(CHAR_SIZE);
    
    m_line_count = width / (CHAR_SIZE - 1);

    m_lines = new MatrixLine*[m_line_count];

    for(int i = 0; i < m_line_count; i++)
    {
        m_lines[i] = new MatrixLine(i, font);
    }

}

void Matrix::update_draw(sf::RenderWindow& window)
{
    
    for(int i = 0; i < m_line_count; i++)
    {
        m_lines[i]->update_draw(window);
    }
}
