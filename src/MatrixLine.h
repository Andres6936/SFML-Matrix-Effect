#pragma once

#include "Symbol.h"
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "MatrixConfig.h"
#include <mutex>

class MatrixLine
{
public:
	MatrixLine(int xOffset, MatrixConfig& config, sf::Font& font);
	void NewLine(int count, int offset);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
private:
	MatrixConfig* m_Config;
	sf::Font& m_font;
	std::vector<Symbol> m_Symbols;
	int m_SymbolCount;
	float m_xOffset;
	float m_Y{0};
	float m_ySpeed;
	float m_Offset{0};

	float RandomDuration() const
	{
		return Random::get().getFloat(
			m_Config->MinSymbolDuration,
			m_Config->MaxSymbolDuration
		);
	}

	int RandomSymbolCount() const
	{
		return Random::get().getInt(
			m_Config->MinLineSymbolCount,
			m_Config->MaxLineSymbolCount
		);
	}

	float RandomSpeed() const
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
