#pragma once
#ifndef BAT_H
#define BAT_H
#include <SFML/Graphics.hpp>
#include "defs.h"

class Bat
{

private:
    Direction m_d;
    const sf::Keyboard::Key m_upKey;
    const sf::Keyboard::Key m_downKey;

    sf::Clock currentTime;

public:
    sf::RectangleShape m_shape;
    Bat(const sf::Vector2f &position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
    void changeDirection(const sf::Keyboard::Key &keyPressed);
    void move();
    void draw(sf::RenderWindow &w);
};

#endif