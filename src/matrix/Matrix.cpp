#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "MatrixLine.h"

Matrix::Matrix(MatrixConfig& config, sf::Font& font)
	: m_Config(&config)
{
	int lineCount = m_Config->Width / (m_Config->CharSize - 1);

	m_Lines.reserve(lineCount);

	for (int i = 0; i < lineCount; i++)
	{
		m_Lines.emplace_back(i, m_Config->CharSize, m_Config->MaxLineSymbolCount, config, font);
	}
}

void Matrix::UpdateDraw(sf::RenderWindow& window, float dt)
{
	for (auto& line : m_Lines)
	{
		line.UpdateDraw(window, dt);
	}
}
