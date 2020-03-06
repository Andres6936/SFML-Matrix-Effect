#include "MatrixLine.h"

#include "Symbol.h"

MatrixLine::MatrixLine(int xOffset, MatrixConfig& config, sf::Font& font)
	: m_Config(&config),
	  m_font(font),
	  m_SymbolCount(RandomSymbolCount()),
	  m_xOffset(xOffset),
	  m_ySpeed(RandomSpeed())
{
	/*
	 * To avoid doing allocations while rendering
	 * preallocated vector is used to reuse symbols.
	 * resize created a bug with the rng
	 */
	m_Symbols.reserve(m_Config->MaxLineSymbolCount);

	int i = 0;
	while (i++ < m_Config->MaxLineSymbolCount)
	{
		m_Symbols.emplace_back(config, font);
	}

	NewLine(m_SymbolCount, 0);
}

void MatrixLine::NewLine(int count, int offset)
{
	m_SymbolCount = count;

	m_Offset = 1.f * (count * m_Config->CharSize) + offset;

	for (int i = 0; i < m_SymbolCount; i++)
	{
		m_Symbols[i].SetFirst(i == m_SymbolCount - 1);

		m_Symbols[i].SetPosition(
			(m_xOffset * m_Config->CharSize),
			(i * m_Config->CharSize - m_Offset)
		);

		m_Symbols[i].SetDuration(RandomDuration());
	}
}

/*
 * Since all lines are independent
 * update and draw can happen one after the other on the same line.
 */
void MatrixLine::Update(float dt)
{
	if (m_Y > m_Config->Height + m_Offset)
	{
		m_Y = 0;
		m_ySpeed = RandomSpeed();
		_newline();
	}

	for (int count = 0; count < m_SymbolCount; count++)
	{
		
		m_Symbols[count].Update(m_ySpeed, dt);
	}

	m_Y += m_ySpeed * dt;
}

void MatrixLine::Draw(sf::RenderWindow& window)
{
	for (int count = 0; count < m_SymbolCount; count++)
	{
		m_Symbols[count].Draw(window);
	}
}
