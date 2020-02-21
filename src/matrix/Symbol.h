#pragma once

#include <SFML/Graphics.hpp>
#include "MatrixConfig.h"
#include "../utils/Math.h"
#include "../utils/Random.h"

class Symbol
{
public:
	Symbol();
	Symbol(MatrixConfig& config, sf::Font& font);

	void Update(float ySpeed, float dt);
	void SetFirst(bool first);
	void SetPosition(sf::Vector2f& pos);
	void SetPosition(float x, float y);
	void SetDuration(float d);

	void Draw(sf::RenderTarget& target) const;
private:
	MatrixConfig* m_Config;
	sf::Text m_Text;
	sf::Vector2f m_Pos;
	sf::Color m_Clr;
	bool m_First{false};
	float m_Dur;
	float m_CurrentTimeStep{0};

	void _RefreshSymbol()
	{
		// 0x30A0 is the start of the unicode katakata chars
		wchar_t c = 0x30A0 + Random::get().getInt(1, 95);

		m_Text.setString(c);

		m_Clr = m_Config->ActiveTextColor;
	}

	void _UpdateClr()
	{
		m_Clr.r = LinearTranslate(0.f, m_Dur, m_Clr.r, m_Config->TextColor.r, m_CurrentTimeStep);
		m_Clr.g = LinearTranslate(0.f, m_Dur, m_Clr.g, m_Config->TextColor.g, m_CurrentTimeStep);
		m_Clr.b = LinearTranslate(0.f, m_Dur, m_Clr.b, m_Config->TextColor.b, m_CurrentTimeStep);
	}
};
