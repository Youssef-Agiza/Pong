
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "bat.hpp"
#include "ball.hpp"

Bat bat1(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
Bat bat2(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
Ball ball(&bat1, &bat2);

void update(sf::RenderWindow &window);
void render(sf::RenderWindow &window);

int main()
{

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong!");

    while (window.isOpen())
    {
        update(window);
        render(window);
    }
    return 0;
}

void update(sf::RenderWindow &window)
{
    sf::Event e;
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    ball.move(dt);

    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window.close();
        if (e.type == sf::Event::KeyPressed)
        {

            bat1.changeDirection(e.key.code);
            bat2.changeDirection(e.key.code);

            if (e.key.code == p1UpKey || e.key.code == p1DownKey)
                bat1.move(dt);

            if (e.key.code == p2UpKey || e.key.code == p2DownKey)
                bat2.move(dt);
        }
    }
}
void render(sf::RenderWindow &window)
{
    window.clear();

    bat1.draw(window);
    bat2.draw(window);

    ball.draw(window);

    window.display();
}
