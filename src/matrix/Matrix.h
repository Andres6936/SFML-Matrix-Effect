#pragma once
#include <SFML/Graphics.hpp>
#include "MatrixConfig.h"
#include "MatrixLine.h"

class Matrix
{
public:
	Matrix(MatrixConfig& config, sf::Font& font);

	void UpdateDraw(sf::RenderWindow& window, float dt);
private:
	MatrixConfig* m_Config;
	std::vector<MatrixLine> m_Lines;
};
