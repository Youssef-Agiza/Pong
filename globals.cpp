#include "globals.h"

Bat *bat1 = new Bat(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
Bat *bat2 = new Bat(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
Ball *ball = new Ball(bat1, bat2);
sf::Event e;
int score1 = 0, score2 = 0;
