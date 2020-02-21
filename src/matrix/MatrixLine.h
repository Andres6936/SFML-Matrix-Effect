#pragma once

#include "Symbol.h"
#include <SFML/Graphics.hpp>
#include "../utils/Random.h"
#include "MatrixConfig.h"

class MatrixLine
{
public:
	MatrixLine(int xOffset, unsigned charSize, unsigned symBufferSize, MatrixConfig& config, sf::Font& font);
	void NewLine(int count, int offset);
	void UpdateDraw(sf::RenderWindow& window, float dt);
private:
	MatrixConfig* m_Config;
	sf::Font& m_font;
	std::vector<Symbol> m_Symbols;
	int m_SymbolCount;
	float m_xOffset;
	float m_Y{0};
	float m_ySpeed;
	float m_Offset{0};

	float RandomDuration()
	{
		return Random::get().getFloat(
			m_Config->MinSymbolDuration,
			m_Config->MaxSymbolDuration
		);
	}

	int RandomSymbolCount()
	{
		return Random::get().getInt(
			m_Config->MinLineSymbolCount,
			m_Config->MaxLineSymbolCount
		);
	}

	float RandomSpeed()
	{
		return Random::get().getFloat(
			m_Config->MinFallSpeed,
			m_Config->MaxFallSpeed
		);
	}

	void _newline()
	{
		NewLine(
			RandomSymbolCount(),
			RandomSymbolCount()
		);
	}
};
