#pragma once

#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "bat.hpp"

class Ball
{

private:
    sf::CircleShape m_shape;
    Bat *m_bat1;
    Bat *m_bat2;

    float m_ballSpeedX;
    float m_ballSpeedY;

    // returns 0 if not collision, 1 if collided with left bat, 2 if collided with right bat, -1 if wall
    int isCollision() const;

public:
    Ball(Bat *bat1, Bat *bat2);
    ~Ball();

    void move(float dt);

    void draw(sf::RenderWindow &w) const;
    void reset();
};

#endif