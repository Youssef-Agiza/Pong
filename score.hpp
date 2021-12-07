#pragma once
#ifndef SCORE_H
#define SCORE_H

// #include "common.h"
// #include <SFML/Graphics.hpp>
#include "common.h"
#include "defs.h"

class Score
{
private:
    sf::Text m_text;
    sf::Font m_font;
    int m_score;

public:
    Score(const sf::Vector2f &position);
    inline int getScore() const { return this->m_score; }
    void setScore(int score);

    void draw(sf::RenderWindow &w);
};

#endif // SCORE_H