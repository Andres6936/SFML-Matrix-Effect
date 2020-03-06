#include "Symbol.h"

Symbol::Symbol()
{
}

Symbol::Symbol(MatrixConfig& config, sf::Font& font)
	: m_Config(&config)
{
	m_Text.setCharacterSize(m_Config->CharSize);
	m_Text.setFont(font);
	_RefreshSymbol();
}

void Symbol::SetFirst(bool first)
{
	m_First = first;
	m_Clr = m_Config->ActiveTextColor;
}

void Symbol::SetPosition(sf::Vector2f& pos)
{
	m_Pos = pos;
}

void Symbol::SetPosition(float x, float y)
{
	m_Pos = {x, y};
}

void Symbol::SetDuration(float d)
{
	m_Dur = d;
}

void Symbol::Update(float ySpeed, float dt)
{
	if (m_CurrentTimeStep >= m_Dur)
	{
		_RefreshSymbol();
		m_CurrentTimeStep = 0;
	}

	m_CurrentTimeStep += m_Config->TimeStep * dt;
	m_Pos.y += ySpeed * dt;

	if (!m_First) _UpdateClr();

	m_Text.setPosition(m_Pos);
	m_Text.setFillColor(m_Clr);
}

void Symbol::Draw(sf::RenderTarget& target) const
{
	target.draw(m_Text);
}
