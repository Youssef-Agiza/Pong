#include "bat.hpp"

Bat::Bat(const sf::Vector2f &position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) : m_upKey(upKey), m_downKey(downKey), m_originalPosition(position)
{
    this->m_shape.setSize(BAT_SIZE);
    this->m_shape.setOrigin(BAT_SIZE / 2.f);
    this->m_shape.setPosition(position);
    this->m_shape.setFillColor(sf::Color::White);
    this->m_direction = Direction::STATIC;
}

void Bat::move(float dt)
{

    auto position = this->m_shape.getPosition();
    if ((position.y + (BAT_SIZE.y / 2.0f)) >= SCREEN_HEIGHT && m_direction == Direction::DOWN)
        return;
    if ((position.y - (BAT_SIZE.y / 2.0f)) <= 0 && m_direction == Direction::UP)
        return;

    this->m_shape.move(0, m_direction * BAT_SPEED * 2.5 * dt); //* BAT_SPEED * dt);
}

void Bat::setPosition(float x, float y)
{
    this->m_shape.setPosition(x, y);
}

void Bat::changeDirection(const sf::Keyboard::Key &keyPressed)
{

    if (keyPressed == this->m_upKey)
        this->m_direction = UP;

    if (keyPressed == this->m_downKey)
        this->m_direction = DOWN;
}

void Bat::draw(sf::RenderWindow &w)
{
    w.draw(this->m_shape);
}

void Bat::reset()
{
    this->m_shape.setPosition(m_originalPosition);
}
