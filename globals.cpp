#include "globals.h"

Bat *bat1 = new Bat(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
Bat *bat2 = new Bat(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
Ball *ball = new Ball(bat1, bat2);
sf::Event e;
Score *score1 = new Score(sf::Vector2f(SCREEN_WIDTH / 2 - 40, 0));
Score *score2 = new Score(sf::Vector2f(SCREEN_WIDTH / 2 + 40, 0));
