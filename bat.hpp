#pragma once
#ifndef BAT_H
#define BAT_H

#include <SFML/Graphics.hpp>
#include "defs.h"

class Bat
{

private:
    sf::RectangleShape m_shape;
    Direction m_direction;
    sf::Vector2f m_originalPosition;

    const sf::Keyboard::Key m_upKey;
    const sf::Keyboard::Key m_downKey;

public:
    Bat(const sf::Vector2f &position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
    void changeDirection(const sf::Keyboard::Key &keyPressed);
    void move(float dt);
    void draw(sf::RenderWindow &w);

    void setPosition(float x, float y);
    inline float getX() const { return this->m_shape.getPosition().x; }
    inline float getY() const { return this->m_shape.getPosition().y; }

    inline const sf::Keyboard::Key &getUpKey() const { return this->m_upKey; };
    inline const sf::Keyboard::Key &getDownKey() const
    {
        return this->m_downKey;
    };

    void reset();
};
#endif