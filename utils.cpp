#include "utils.h"

void render(sf::RenderWindow &window)
{
    window.clear();

    bat1->draw(window);
    bat2->draw(window);
    ball->draw(window);

    window.display();
}

void child_logic()
{

    key_t key = ftok("shmfile", 65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    // shmat to attach to shared memory
    sharedMemData *sharedData = (sharedMemData *)shmat(shmid, (void *)0, 0);

    sf::RenderWindow window1(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong 1!");
    initialize_shared_data(*sharedData);
    while (window1.isOpen())
    {

        read_bats(*sharedData);
        read_ball(*sharedData);
        update_bats_on_event(window1, *sharedData);
        write_bats(*sharedData);
        render(window1);
    }

    shmdt(sharedData);
    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
}

void parent_logic()
{
    key_t key = ftok("shmfile", 65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    // shmat to attach to shared memory
    sharedMemData *sharedData = (sharedMemData *)shmat(shmid, (void *)0, 0);
    initialize_shared_data(*sharedData);

    while (!sharedData->gameOver)
    {
        update_dt(*sharedData);
        read_bats(*sharedData);
        update_ball(*sharedData);
        // write here
        write_ball(*sharedData);
    }
    // detach from shared memory
    shmdt(sharedData);
}

void clean()
{
    delete bat1, bat2, ball, e;
}