#include "MatrixLine.h"

#include "Symbol.h"
#include "../utils/Random.h"

#include <iostream>

int MatrixLine::s_char_pos_offset = 0;
int MatrixLine::s_char_size = 18;
int MatrixLine::s_HEIGHT;

int get_simbol_length()
{
    return Random::get().getInt(10, 50);
}

float get_step()
{
    return Random::get().getFloat(3, 6);
}

void MatrixLine::setHeight(int height)
{ 
    MatrixLine::s_HEIGHT = height;
}

MatrixLine::MatrixLine() {
    m_font = sf::Font();
}

MatrixLine::MatrixLine(int x, sf::Font& font)
:   m_step(get_step()),
    m_symbols_size(get_simbol_length()),
    m_row(x),
    m_font(font)
{
    Symbol::s_size = s_char_size;
    create_line(m_symbols_size, 0);
}

// The worst variable naming scheme
void MatrixLine::create_line(int size, int offset)
{
    m_symbols_size = size;
    m_symbols = new Symbol[size];
    m_offset = 1.f * (size * s_char_size) + offset;
    float x = (m_row * (s_char_size - s_char_pos_offset));
    
    for (int i = 0; i < size; i++)
    {
        float y = ((i * s_char_size) - m_offset) - s_char_pos_offset;
        float duration = 10 * Random::get().getFloat(1, 10);
        m_symbols[i] = Symbol(m_font, x, y, duration, i == size - 1);
    }
}

void MatrixLine::update_draw(sf::RenderWindow& window)
{
    if (m_y > s_HEIGHT + m_offset)
    {
        m_y = 0;   
        purge_symbols();
        m_step = get_step();
        create_line(
            get_simbol_length(),
            Random::get().getInt(4, 10) * m_symbols_size
        );
    }

    for (int i = 0; i < m_symbols_size; i++)
    {
        m_symbols[i].update(m_step);
        m_symbols[i].draw(window);
    }

    m_y += m_step;
}

void MatrixLine::set_char_size(int s)
{
    Symbol::s_size = s;
    MatrixLine::s_char_size = s;
}

void MatrixLine::purge_symbols()
{
    delete [] m_symbols;
}