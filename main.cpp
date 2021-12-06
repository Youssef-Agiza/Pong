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

Bat bat2(sf::Vector2f(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2.f), p2UpKey, p2DownKey);
Bat bat1(sf::Vector2f(10, SCREEN_HEIGHT / 2.f), p1UpKey, p1DownKey);
Ball ball(&bat1, &bat2);
bool gameOver = false;

void update(sf::RenderWindow &window);
void render(sf::RenderWindow &window);

key_t key = ftok("shmfile", 65);
int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
float *ballX = (float *)shmat(shmid, (void *)0, 0);

int main(int argc, char **argv)
{

    // sf::Vector2f *bat1Pos = (sf::Vector2f *)shmat(shmid, (void *)0, 0);
    // sf::Vector2f *bat2Pos = (sf::Vector2f *)shmat(shmid, (void *)0, 0);

    pid_t child_a, child_b;

    child_a = fork();
    if (child_a == 0)
    {
        // key_t key = ftok("shmfile", 65);

        sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 1!");
        while (window.isOpen())
        {
            update(window);
            render(window);
        }
    }
    else
    {
        child_b = fork();
        if (child_b == 0)
        {
            // key_t key = ftok("shmfile", 65);

            // int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
            sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 2!");
            while (window.isOpen())
            {

                update(window);
                render(window);
            }

            // destroy the shared memory
            shmctl(shmid, IPC_RMID, NULL);
        }
    }

    return 0;
}

void update(sf::RenderWindow &window)
{
    sf::Event e;
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

// // #include <boost/interprocess/shared_memory_object.hpp>
// // #include <boost/interprocess/mapped_region.hpp>
// // #include <iostream>
// // #include <cstring>
// // #include <cstdlib>
// // #include <string>

// // int main(int argc, char *argv[])
// // {
// //     using namespace boost::interprocess;
// //     pid_t child_a, child_b;

// //     child_a = fork();
// //     if (child_a == 0)
// //     {
// //         std::cout << "child";
// //         // Open already created shared memory object.
// //         shared_memory_object shm(open_only, "MySharedMemory", read_only);
// //         // Map the whole shared memory in this process
// //         mapped_region region(shm, read_only);
// //         // Check that memory was initialized to 1
// //         char *mem = static_cast<char *>(region.get_address());
// //         for (std::size_t i = 0; i < region.get_size(); ++i)
// //             if (*mem++ != 1)
// //                 return 1; // Error checking memory
// //     }

// //     else
// //     { // Parent process
// //         // Remove shared memory on construction and destruction
// //         std::cout << "parent";
// //         // struct shm_remove
// //         // {
// //         //     shm_remove() { shared_memory_object::remove("MySharedMemory"); }
// //         //     ~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
// //         // } remover;

// //         // Create a shared memory object.
// //         shared_memory_object shm(create_only, "MySharedMemory", read_write);

// //         // Set size
// //         shm.truncate(1000);

// //         // Map the whole shared memory in this process
// //         mapped_region region(shm, read_write);

// //         // Write all the memory to 1
// //         std::memset(region.get_address(), 1, region.get_size());

// //         // Launch child process
// //         // std::string s(argv[0]);
// //         // s += " child ";
// //         // std::cout << "begin   " << s << "   end";
// //         // if (0 != std::system(s.c_str()))
// //         return 1;
// //     }

// //     return 0;
// // }