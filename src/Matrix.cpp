#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "MatrixLine.h"

Matrix::Matrix()
	:
	m_ConfigFile("matrix.cfg")
{
	Random::init();
	RefreshConfig();
	LoadRes();

	const sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();

	m_Config.Width = CurrentDesktopMode.width;
	m_Config.Height = CurrentDesktopMode.height;

	m_Window = std::make_unique<sf::RenderWindow>(
		CurrentDesktopMode,
		"Matrix",
		sf::Style::Fullscreen
	);

	m_Window->setActive(false);
	if (m_Config.FrameRate != 0) m_Window->setFramerateLimit(m_Config.FrameRate);

	m_Window->setVerticalSyncEnabled(m_Config.VerticalSync);

	__initLineBuffer();
}

void Matrix::RefreshConfig()
{
	const auto defaults = __getDefaultConfig();
	if (!m_ConfigFile.isValid())
	{
		m_Config = defaults;
	}
	else
	{
		m_ConfigFile.Refresh();

		m_Config.CharSize = m_ConfigFile.GetIfProp<int>("CharSize", defaults.CharSize);
		m_Config.VerticalSync = m_ConfigFile.GetIfProp<bool>("VerticalSync", defaults.VerticalSync);
		m_Config.FrameRate = m_ConfigFile.GetIfProp<bool>("FrameRate", defaults.FrameRate);
		m_Config.MinSymbolDuration = m_ConfigFile.GetIfProp<float>("MinSymbolDuration", defaults.MinSymbolDuration);
		m_Config.MaxSymbolDuration = m_ConfigFile.GetIfProp<float>("MaxSymbolDuration", defaults.MaxSymbolDuration);
		m_Config.MinLineSymbolCount = m_ConfigFile.GetIfProp<int>("MinLineSymbolCount", defaults.MinLineSymbolCount);
		m_Config.MaxLineSymbolCount = m_ConfigFile.GetIfProp<int>("MaxLineSymbolCount", defaults.MaxLineSymbolCount);
		m_Config.MinFallSpeed = m_ConfigFile.GetIfProp<float>("MinFallSpeed", defaults.MinFallSpeed);
		m_Config.MaxFallSpeed = m_ConfigFile.GetIfProp<float>("MaxFallSpeed", defaults.MaxFallSpeed);
		m_Config.TimeStep = m_ConfigFile.GetIfProp<int>("TimeStep", defaults.TimeStep);
		m_Config.BackgroundColor = m_ConfigFile.GetIfProp<sf::Color>("BackgroundColor", defaults.BackgroundColor);
		m_Config.TextColor = m_ConfigFile.GetIfProp<sf::Color>("TextColor", defaults.TextColor);
		m_Config.ActiveTextColor = m_ConfigFile.GetIfProp<sf::Color>("ActiveTextColor", defaults.ActiveTextColor);
		m_Config.ColorFalloffFactor = m_ConfigFile.GetIfProp<float>("ColorFalloffFactor", defaults.ColorFalloffFactor);

		m_ConfigFile.PrintEntries();
	}
}

void Matrix::LoadRes()
{
	if (!m_Font.loadFromFile("res/font.otf"))
	{
		std::cerr << "Cannot load font.\n";
	}
}

void Matrix::Run()
{
	float temp;
	float newTime = m_Clock.getElapsedTime().asSeconds();
	float dt;

	while (m_Window->isOpen())
	{
		sf::Event e;

		while (m_Window->pollEvent(e))
		{
			__handleEvents(e);
		}

		temp = newTime;
		newTime = m_Clock.getElapsedTime().asSeconds();

		dt = std::clamp(newTime - temp, 0.f, FIXED_DT);

		m_Window->clear(m_Config.BackgroundColor);

		for (auto& line : m_Lines)
		{
			line.Update(dt);
			line.Draw(*m_Window);
		}

		m_Window->display();
	}
}
