#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#include "bat.hpp"
#include "ball.hpp"
#include "score.hpp"
#include "defs.h"

extern Bat *bat1;  //(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
extern Bat *bat2;  //(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
extern Ball *ball; //(&bat1, &bat2);
extern sf::Event e;
extern Score *score1;
extern Score *score2;
#endif // GLOBAL_H