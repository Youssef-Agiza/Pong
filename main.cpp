#include <SFML/Graphics.hpp>

#include <iostream>
#include "bat.hpp"
#include "ball.hpp"

int main()
{
    Bat bat(sf::Vector2f(10, 100), sf::Keyboard::W, sf::Keyboard::S);
    Bat bat2(sf::Vector2f(SCREEN_WIDTH - 20, 100), sf::Keyboard::Up, sf::Keyboard::Down);
    Ball ball;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong!");

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed)
            {
                bat.changeDirection(e.key.code);
                bat.move();
                bat2.move();
                bat2.changeDirection(e.key.code);
            }
        }

        window.clear();

        bat.draw(window);
        bat2.draw(window);

        ball.draw(window);

        window.display();
    }
    return 0;
}