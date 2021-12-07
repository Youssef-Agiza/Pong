
#include "score.hpp"

Score::Score(const sf::Vector2f &position)
{

    // sf::Text text;
    // sf::RenderWindow w(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 1!");
    if (!m_font.loadFromFile("font.ttf"))
    {
        // error...
        exit(-1);
    }
    m_text.setFont(m_font); // font is a sf::Font
    m_text.setString("0");
    m_text.setCharacterSize(44); // in pixels, not points!
    m_text.setFillColor(sf::Color::White);
    m_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    m_text.setPosition(position);
}

void Score::setScore(int score)
{
    this->m_score = score;
    this->m_text.setString(std::to_string(score));
}

void Score::draw(sf::RenderWindow &w)
{
    w.draw(this->m_text);
}