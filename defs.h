#pragma once
#ifndef DEFS_H
#define DEFS_H
#include <SFML/Graphics.hpp>

// screen
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400

// bats
#define BAT_SPEED 50000.f
const sf::Vector2f BAT_SIZE(10, 100);

// ball
#define BALL_RADIUS 5
#define BALL_SPEED_X 100
#define BALL_SPEED_Y 60

// controls
const sf::Keyboard::Key p1UpKey = sf::Keyboard::W;
const sf::Keyboard::Key p1DownKey = sf::Keyboard::S;
const sf::Keyboard::Key p2UpKey = sf::Keyboard::Up;
const sf::Keyboard::Key p2DownKey = sf::Keyboard::Down;

// directoins
enum Direction
{
    STATIC = 0,
    UP = -1,
    DOWN = 1,
};

#endif // DEFS_H