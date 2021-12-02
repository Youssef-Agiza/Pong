#include "ball.hpp"
#include "defs.h"

Ball::Ball()
{
    this->m_shape.setRadius(RADIUS);
    this->m_shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void Ball ::draw(sf::RenderWindow &w) const
{
    w.draw(this->m_shape);
}