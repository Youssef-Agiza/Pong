#include <iostream>
#include <SFML/Graphics.hpp>
#include "bat.hpp"
#include "ball.hpp"
// #include <boost/interprocess/shared_memory_object.hpp>
// #include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
namespace bip = boost::interprocess;

struct newPositions
{
    // sf::Vector2f ball;
    // sf::Vector2f bat1;
    // sf::Vector2f bat2;
    float bat1Y;
    float bat2Y;
    int score;
};

/*

parent -->  child:
    new ball position
    new bat 1 position
    new bat 2 position


*/
/*
1- struct for the data to be shared:
    - position for the ball
    - position for the bat1
    - position for the bat2
    - score

2- create shared memory:
    - parent will move the ball, get the new position, then pass to the children.
    -

3-

4-


*/

Bat bat1(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
Bat bat2(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
Ball ball(&bat1, &bat2);
int score = 0;

void update(sf::RenderWindow &window);
void render(sf::RenderWindow &window);

void reader(const newPositions &pos, Bat &bat1, Bat &bat2, int &score);
void writer(newPositions &pos, const Bat &bat1, const Bat &bat2, const int &score);

pid_t child_a, child_b;
sf::Event e;

int main(int argc, char **argv)
{

    child_a = fork();
    if (child_a == 0)
    {
        key_t key = ftok("shmfile", 65);
        // shmget returns an identifier in shmid
        int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
        // shmat to attach to shared memory
        newPositions *sharedPos = (newPositions *)shmat(shmid, (void *)0, 0);

        sf::RenderWindow window1(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 1!");

        while (window1.isOpen())
        {
            reader(*sharedPos, bat1, bat2, score);
            update(window1);

            // write here
            writer(*sharedPos, bat1, bat2, score);
            render(window1);
        }

        // destroy the shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        child_b = fork();
        if (child_b == 0)
        {
            key_t key = ftok("shmfile", 65);
            // shmget returns an identifier in shmid
            int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
            // shmat to attach to shared memory
            newPositions *sharedPos = (newPositions *)shmat(shmid, (void *)0, 0);

            sf::RenderWindow window2(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 2!");
            while (window2.isOpen())
            {
                reader(*sharedPos, bat1, bat2, score);
                update(window2);

                writer(*sharedPos, bat1, bat2, score);
                render(window2);
            }

            // destroy the shared memory
            shmctl(shmid, IPC_RMID, NULL);
        }
        else
        {
            key_t key = ftok("shmfile", 65);
            // shmget returns an identifier in shmid
            int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
            // shmat to attach to shared memory
            char *str = (char *)shmat(shmid, (void *)0, 0);

            // detach from shared memory
            shmdt(str);
        }
    }

    return 0;
}

void update(sf::RenderWindow &window)
{
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    ball.move(dt);

    float ballX = ball.getX(), ballY = ball.getY();
    // float
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window.close();
        if (e.type == sf::Event::KeyPressed)
        {

            bat1.changeDirection(e.key.code);
            bat2.changeDirection(e.key.code);

            if (e.key.code == p1UpKey || e.key.code == p1DownKey)
                bat1.move(dt);

            if (e.key.code == p2UpKey || e.key.code == p2DownKey)
                bat2.move(dt);
        }
    }
}
void render(sf::RenderWindow &window)
{
    window.clear();

    bat1.draw(window);
    bat2.draw(window);
    ball.draw(window);

    window.display();
}

void reader(const newPositions &pos, Bat &bat1, Bat &bat2, int &score)
{
    float bat1Y = pos.bat1Y;
    float bat2Y = pos.bat2Y;
    bat1.setPosition(bat1.getX(), bat1Y);
    bat2.setPosition(bat2.getX(), bat2Y);

    score = pos.score;
}
void writer(newPositions &pos, const Bat &bat1, const Bat &bat2, const int &score)
{
    pos.bat1Y = bat1.getY();
    pos.bat2Y = bat2.getY();
    pos.score = 0;
}