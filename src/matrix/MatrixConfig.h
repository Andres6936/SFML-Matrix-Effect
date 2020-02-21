#pragma once
#include <SFML/Graphics/Color.hpp>

struct MatrixConfig
{
	int Width;
	int Height;
	int CharSize;
	bool VerticalSync;
	int FrameRate;
	float MinSymbolDuration;
	float MaxSymbolDuration;
	int MinLineSymbolCount;
	int MaxLineSymbolCount;
	float MinFallSpeed;
	float MaxFallSpeed;
	int TimeStep;
	sf::Color BackgroundColor;
	sf::Color TextColor;
	sf::Color ActiveTextColor;
};