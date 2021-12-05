
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

void update(sf::RenderWindow &window);
void render(sf::RenderWindow &window);

int main(int argc, char **argv)
{

    pid_t child_a, child_b;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 2");
    child_a = fork();

    if (child_a == 0)
    {
        std::cout << "child 1";
        // Open already created shared memory object.
        bip::shared_memory_object shm(bip::open_only, "MySharedMemory", bip::read_only);

        // Map the whole shared memory in this process
        bip::mapped_region region(shm, bip::read_only);

        // Check that memory was initialized to 1
        char *mem = static_cast<char *>(region.get_address());
    }
    else
    {
        child_b = fork();

        if (child_b == 0)
        {
            std::cout << "child 2";

            // Open already created shared memory object.
            bip::shared_memory_object shm(bip::open_only, "MySharedMemory", bip::read_only);

            // Map the whole shared memory in this process
            bip::mapped_region region(shm, bip::read_only);

            // Check that memory was initialized to 1
            char *mem = static_cast<char *>(region.get_address());
            std::cout << *mem;
        }
        else
        {
            std::cout << "parent";

            struct shm_remove
            {
                shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
                ~shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
            } remover;

            // Create a shared memory object.
            bip::shared_memory_object shm(bip::create_only, "MySharedMemory", bip::read_write);

            // Set size
            shm.truncate(1000);

            // Map the whole shared memory in this process

            // Write all the memory to 1
            bip::mapped_region region(shm, bip::read_write);

            std::memset(region.get_address(), 1, 10);

            // Launch child process
        }
    }

    // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong!");
    //  while (window.isOpen())
    //  {
    //      update(window);
    //      render(window);
    //  }

    return 0;
}

void update(sf::RenderWindow &window)
{
    sf::Event e;
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    ball.move(dt);

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
