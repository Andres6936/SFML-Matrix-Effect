#pragma once
#include <SFML/Graphics.hpp>
#include "MatrixConfig.h"
#include "MatrixLine.h"
#include "ConfigFile.h"

class Matrix
{
public:
	Matrix();

	void LoadRes();
	void Run();
	void RefreshConfig();

private:
	const float FIXED_DT = 0.020f;
	
	std::unique_ptr<sf::RenderWindow> m_Window;
	MatrixConfig m_Config;
	ConfigFile m_ConfigFile;
	std::vector<MatrixLine> m_Lines;
	sf::Font m_Font;
	sf::Clock m_Clock;
	
	void __initLineBuffer()
	{
		int lineCount = m_Config.Width / (m_Config.CharSize - 1);
		
		m_Lines.reserve(lineCount);

		for (int i = 0; i < lineCount; i++) 
			m_Lines.emplace_back(i, m_Config, m_Font);
	}
	
	static MatrixConfig __getDefaultConfig()
	{
		MatrixConfig o;

		o.CharSize = 18;
		o.VerticalSync = true;
		o.FrameRate = 0;
		o.MinSymbolDuration = 10;
		o.MaxSymbolDuration = 40;
		o.MinLineSymbolCount = 10;
		o.MaxLineSymbolCount = 35;
		o.MinFallSpeed = 100;
		o.MaxFallSpeed = 400;
		o.TimeStep = 10;
		o.BackgroundColor = sf::Color(0, 0, 0);
		o.TextColor = sf::Color(0, 255, 0);
		o.ActiveTextColor = sf::Color(220, 220, 220);
		o.ColorFalloffFactor = 1;

		return o;
	}

	void __handleEvents(sf::Event& e)
	{
		switch (e.type)
		{
		case sf::Event::Closed: m_Window->close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape: m_Window->close();
				break;
			case sf::Keyboard::R: RefreshConfig();
				break;
			default: break;
			}
			break;
		default: break;
		}
	}
};
