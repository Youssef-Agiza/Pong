#include "ball.hpp"
#include "bat.hpp"

Ball::Ball(Bat *bat1, Bat *bat2) : m_bat1(bat1), m_bat2(bat2), m_ballSpeedX(-BALL_SPEED_X), m_ballSpeedY(BALL_SPEED_Y)
{
    this->m_shape.setRadius(BALL_RADIUS);
    this->m_shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    this->m_shape.setOrigin(BALL_RADIUS / 2, BALL_RADIUS / 2);
}

Ball ::~Ball()
{
    this->m_bat1 = nullptr;
    this->m_bat2 = nullptr;
}
void Ball ::draw(sf::RenderWindow &w) const
{
    w.draw(this->m_shape);
}

void Ball::reset()
{
    this->m_bat1->reset();
    this->m_bat2->reset();
    this->m_shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    m_ballSpeedX = BALL_SPEED_X;
    m_ballSpeedY = BALL_SPEED_Y;
}

void Ball::setPosition(float x, float y)
{
    this->m_shape.setPosition(x, y);
}

int Ball::move(float dt)
{
    float bat1X = this->m_bat1->getX();
    float bat1Y = this->m_bat1->getY();
    float bat2X = this->m_bat2->getX();
    float bat2Y = this->m_bat2->getY();

    float ballX = this->m_shape.getPosition().x;
    float ballY = this->m_shape.getPosition().y;

    if (ballY >= SCREEN_HEIGHT || ballY <= 0) // collide with bottom
    {
        m_ballSpeedX *= BALL_SPEED_FACTOR;
        m_ballSpeedY *= -BALL_SPEED_FACTOR;

        if (ballY >= SCREEN_HEIGHT)
            this->m_shape.move(0, -10);
        else
            this->m_shape.move(0, 10);
        return 0;
    }
    else if (ballX >= SCREEN_WIDTH || ballX <= 0)
    {
        int res = (ballX >= SCREEN_WIDTH) ? 1 : -1;
        this->reset();
        return res;
    }

    else if (ballX <= BAT_SIZE.x &&                // bat x cooridantes
             ballY < bat1Y + (BAT_SIZE.y * 0.5) && // bat bottom edge
             ballY > bat1Y - (BAT_SIZE.y * 0.5))   // bat top edge
    {

        m_ballSpeedX *= -BALL_SPEED_FACTOR;

        if (ballY > bat1Y) // top part
            m_ballSpeedY *= (m_ballSpeedY > 0) ? BALL_SPEED_FACTOR : -BALL_SPEED_FACTOR;
        else if (ballY < bat1Y) // bottom part
            m_ballSpeedY *= (m_ballSpeedY < 0) ? BALL_SPEED_FACTOR : -BALL_SPEED_FACTOR;
        else
            m_ballSpeedY = 0;
    }
    else if (ballX >= (SCREEN_WIDTH - BAT_SIZE.x) && // bat x cooridantes
             ballY < bat2Y + (BAT_SIZE.y * 0.5) &&   // bat bottom edge
             ballY > bat2Y - (BAT_SIZE.y * 0.5))     // bat top edge
    {
        m_ballSpeedX *= -BALL_SPEED_FACTOR;

        if (ballY > bat2Y) // top part
            m_ballSpeedY *= (m_ballSpeedY > 0) ? BALL_SPEED_FACTOR : -BALL_SPEED_FACTOR;
        else if (ballY < bat2Y) // bottom part
            m_ballSpeedY *= (m_ballSpeedY < 0) ? BALL_SPEED_FACTOR : -BALL_SPEED_FACTOR;
        else
            m_ballSpeedY = 0;
    }
    this->m_shape.move(m_ballSpeedX * dt, m_ballSpeedY * dt);
    return 0;
}
