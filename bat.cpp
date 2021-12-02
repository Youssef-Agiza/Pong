#include "bat.hpp"

Bat::Bat(const sf::Vector2f &position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) : m_upKey(upKey), m_downKey(downKey)
{
    this->m_shape.setSize(sf::Vector2f(BAT_WIDTH, BAT_HEIGHT));
    this->m_shape.setPosition(position);
    this->m_shape.setFillColor(sf::Color::White);
    this->m_d = Direction::STATIC;
    this->m_shape.setOutlineColor(sf::Color::Red);
    this->m_shape.setOutlineThickness(1);
}

void Bat::move()
{
    if (currentTime.getElapsedTime().asMilliseconds() < SPEED_TIMER)
        return;

    const float step = (this->m_d == Direction::STATIC) ? 0 : (this->m_d == Direction::UP) ? -STEP_SIZE
                                                                                           : STEP_SIZE;
    auto position = this->m_shape.getPosition();
    const float curY = position.y;

    if ((curY - step <= 0 && m_d == Direction::UP) ||
        (curY + step >= SCREEN_HEIGHT && m_d == Direction::DOWN))
        return;

    this->m_shape.move(0, step);
    currentTime.restart();
}

void Bat::changeDirection(const sf::Keyboard::Key &keyPressed)
{

    if (keyPressed == this->m_upKey)
        this->m_d = UP;

    if (keyPressed == this->m_downKey)
        this->m_d = DOWN;
}

void Bat::draw(sf::RenderWindow &w)
{
    w.draw(this->m_shape);
}