#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils/Random.h"
#include "matrix/Matrix.h"
#include "matrix/ConfigFile.h"
#include "matrix/MatrixConfig.h"


MatrixConfig getDefaultConfig()
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

    return o;
}

void RefreshConfig(MatrixConfig& o, ConfigFile& conFile)
{
    const auto defaults = getDefaultConfig();
	if (!conFile.isValid())
	{   
        o = defaults;
	}
	else
	{
        conFile.Refresh();
		
        o.CharSize              = conFile.GetIfProp<int>("CharSize", defaults.CharSize);
        o.VerticalSync          = conFile.GetIfProp<bool>("VerticalSync", defaults.VerticalSync);
        o.FrameRate             = conFile.GetIfProp<bool>("FrameRate", defaults.FrameRate);
        o.MinSymbolDuration     = conFile.GetIfProp<float>("MinSymbolDuration", defaults.MinSymbolDuration);
        o.MaxSymbolDuration     = conFile.GetIfProp<float>("MaxSymbolDuration", defaults.MaxSymbolDuration);
        o.MinLineSymbolCount    = conFile.GetIfProp<int>("MinLineSymbolCount", defaults.MinLineSymbolCount);
		o.MaxLineSymbolCount    = conFile.GetIfProp<int>("MaxLineSymbolCount", defaults.MaxLineSymbolCount);
        o.MinFallSpeed          = conFile.GetIfProp<float>("MinFallSpeed", defaults.MinFallSpeed);
        o.MaxFallSpeed          = conFile.GetIfProp<float>("MaxFallSpeed", defaults.MaxFallSpeed);
		o.TimeStep              = conFile.GetIfProp<int>("TimeStep", defaults.TimeStep);
		o.BackgroundColor       = conFile.GetIfProp<sf::Color>("BackgroundColor", defaults.BackgroundColor);
        o.TextColor             = conFile.GetIfProp<sf::Color>("TextColor", defaults.TextColor);
        o.ActiveTextColor       = conFile.GetIfProp<sf::Color>("ActiveTextColor", defaults.ActiveTextColor);

        conFile.PrintEntries();
	}
}

int main()
{
    Random::init();
    MatrixConfig config;
    ConfigFile conf("matrix.cfg");

    RefreshConfig(config, conf);
	
    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();

    config.Width = CurrentDesktopMode.width;
    config.Height = CurrentDesktopMode.height;
	
    sf::RenderWindow window(
        CurrentDesktopMode,
        "Matrix",
        sf::Style::Fullscreen
    );


    if (config.FrameRate != 0) window.setFramerateLimit(config.FrameRate);
    window.setVerticalSyncEnabled(config.VerticalSync);

    sf::Font font;
    // Font that support unicode katakana chars
    if (!font.loadFromFile("res/font.otf"))
    {
        std::cout << "Cannot load font.\n";
    }

    Matrix M = Matrix(config, font);
	
    float frameTime = 0;

    sf::Clock clock;
	
    float temp;
    float newTime = clock.getElapsedTime().asSeconds();
    float fixedDT = 0.020f;
	
	while (window.isOpen())
    {
        sf::Event e; 

        while (window.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed: window.close(); break;
                case sf::Event::KeyPressed:
                    switch(e.key.code)
                    {
                        case sf::Keyboard::Escape: window.close(); break;
                        case sf::Keyboard::R: RefreshConfig(config, conf); break;
                        default: break;
                    }
                break;
                default: break;
            }
        }

        temp = newTime;
        newTime = clock.getElapsedTime().asSeconds();
		
        frameTime = newTime - temp;

        frameTime = std::clamp(frameTime, 0.f, fixedDT);
		
        window.clear(config.BackgroundColor);
		
        M.UpdateDraw(window, frameTime);

        window.display();
    }

    return 0;
}
