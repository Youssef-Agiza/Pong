#include "sharedMem.h"

void update_bats_on_event(sf::RenderWindow &window, sharedMemData &pos)
{
    // float dt = pos.dt;
    // float dt = 0.0000000001;
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();
    // std::cout << dt;
    // float
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window.close();
        if (e.type == sf::Event::KeyPressed)
        {

            bat1->changeDirection(e.key.code);
            bat2->changeDirection(e.key.code);

            if (e.key.code == p1UpKey || e.key.code == p1DownKey)
                bat1->move(dt);

            if (e.key.code == p2UpKey || e.key.code == p2DownKey)
                bat2->move(dt);
        }
    }
}

void initialize_shared_data(sharedMemData &sharedData)
{
    sharedData.bat1Y = SCREEN_HEIGHT / 2;
    sharedData.bat2Y = SCREEN_HEIGHT / 2;
}
void update_ball(const sharedMemData &pos)
{
    ball->move(pos.dt);
}

void update_dt(sharedMemData &sharedMem)
{
    static sf::Clock clock;
    sharedMem.dt = clock.restart().asSeconds();
}
void read_ball(const sharedMemData &pos)
{
    ball->setPosition(pos.ballX, pos.ballY);
}
void write_ball(sharedMemData &pos)
{
    pos.ballX = ball->getX();
    pos.ballY = ball->getY();
}

void read_bats(const sharedMemData &pos)
{
    bat1->setPosition(bat1->getX(), pos.bat1Y);
    bat2->setPosition(bat2->getX(), pos.bat2Y);
}
void write_bats(sharedMemData &pos)
{
    pos.bat1Y = bat1->getY();
    pos.bat2Y = bat2->getY();
}

void read_score(const sharedMemData &pos)
{
    score1 = pos.score1;
    score2 = pos.score2;
}
void write_score(sharedMemData &pos)
{
    pos.score1 = score1;
    pos.score2 = score2;
}