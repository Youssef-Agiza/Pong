#pragma once

#ifndef BALL_H
#define BALL_H

#include "common.h"
#include "defs.h"
class Bat;
class Ball
{

private:
    sf::CircleShape m_shape;
    Bat *m_bat1;
    Bat *m_bat2;

    float m_ballSpeedX;
    float m_ballSpeedY;

public:
    Ball(Bat *bat1, Bat *bat2);
    ~Ball();

    // returns 1 if player 2 lost, -1 if player 1
    int move(float dt);

    void setPosition(float x, float y);
    float getX() const { return this->m_shape.getPosition().x; }
    float getY() const { return this->m_shape.getPosition().y; }

    void draw(sf::RenderWindow &w) const;
    void reset();
};

#endif