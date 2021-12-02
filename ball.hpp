#pragma once

#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

class Ball
{

private:
    sf::CircleShape m_shape;

public:
    Ball();

    // void move();
    // void changeDirection();

    void draw(sf::RenderWindow &w) const;
};

#endif