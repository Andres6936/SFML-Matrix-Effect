#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils/Random.h"
#include "matrix/Matrix.h"

int main()
{
    Random::init();

    sf::VideoMode CurrentDesktopMode = sf::VideoMode::getDesktopMode();

    const int WIDTH = CurrentDesktopMode.width;
    const int HEIGHT = CurrentDesktopMode.height;

    sf::RenderWindow window(
        CurrentDesktopMode,
        "Matrix",
        sf::Style::Fullscreen
    );

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    // Font that support unicode katakana chars
    if (!font.loadFromFile("res/font.otf"))
    {
        std::cout << "Cannot load font.\n";
    }

    Matrix M = Matrix(WIDTH, HEIGHT, font);

    sf::RectangleShape bgRect;

    bgRect.setFillColor(sf::Color(0, 0, 0, 185));
    bgRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

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
                    }
                break;
            }
        }

        window.draw(bgRect); // use of a black rect to create trailing effec

        //window.clear(sf::Color(0, 0, 0));

        M.update_draw(window);

        window.display();
    }


    return 0;
}