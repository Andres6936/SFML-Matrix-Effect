#include "Symbol.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../utils/Random.h"

int Symbol::s_size = 24;
sf::Color Symbol::s_clr = sf::Color(0, 125, 0);
sf::Color Symbol::s_first_clr = sf::Color(225, 255, 225);

Symbol::Symbol() {}

Symbol::Symbol(sf::Font& font, float x, float offset_y, float duration, bool isfirst)
:   m_x(x),
    m_y(offset_y),
    m_duration(duration),
    m_isfirst(isfirst)
{
    m_text.setFont(font);
    newchar();
    m_text.setCharacterSize(Symbol::s_size);


    if(isfirst)
        m_clr = s_first_clr;
    else
        m_clr = s_clr;
}

void Symbol::update_clr()
{
    int red = m_clr.r;
    int green = m_clr.g;
    int blue = m_clr.b;

    uint8_t ddred = s_clr.r;
    uint8_t ddgreen = s_clr.g;
    uint8_t ddblue = s_clr.b;

    float kr = (red - ddred) / m_duration;
    float kg = (green - ddgreen) / m_duration;
    float kb = (blue - ddblue) / m_duration;

    if (red >= ddred)
        red = (int) (red - kr);

    if (green >= ddgreen)
        green = (int) (green - kg);   

    if (blue >= ddblue)
        blue = (int) (blue - kb);

    if (red <= s_clr.r && green <= s_clr.g && blue <= s_clr.b)
        m_clr = s_clr;

    m_clr.r = red;
    m_clr.g = green;
    m_clr.b = blue;
}

void Symbol::newchar()
{
    // 0x30A0 is the start of the unicode katakata chars
    wchar_t c = 0x30A0 + Random::get().getInt(1, 95);

    m_text.setString(c);

    m_clr.r = (sf::Uint8) (s_first_clr.r * 0.8);
    m_clr.g = (sf::Uint8) (s_first_clr.g * 0.8);
    m_clr.b = (sf::Uint8) (s_first_clr.b * 0.8);
}

void Symbol::update(float step)
{
    if (m_current_timestamp >=  m_duration)
    {
        newchar();
        m_current_timestamp = 0;
    }

    m_current_timestamp += 0.5;

    m_y += step;

    if (!m_isfirst)
    {
        update_clr();
    }

    m_text.setPosition(m_x, m_y);
    m_text.setFillColor(m_clr);
}

void Symbol::draw(sf::RenderWindow& window)
{
    window.draw(m_text);
}
