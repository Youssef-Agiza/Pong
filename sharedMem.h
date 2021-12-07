#pragma once

#ifndef SHARED_MEM_H
#define SHARED_MEM_H
#include "common.h"
#include "defs.h"
#include "globals.h"

class Bat;
class Ball;

struct sharedMemData
{
    float ballX;
    float ballY;
    float bat1Y;
    float bat2Y;
    int score1;
    int score2;
    float dt;
    bool gameOver;
};

void initialize_shared_data(sharedMemData &sharedData);

void update_ball(sharedMemData &pos);

void update_dt(sharedMemData &sharedMem);

void update_bats_on_event(sf::RenderWindow &window, sharedMemData &pos);

void read_bats(const sharedMemData &pos);
void write_bats(sharedMemData &pos);

void read_ball(const sharedMemData &pos);
void write_ball(sharedMemData &pos);

void read_score(const sharedMemData &pos);
void write_score(sharedMemData &pos);

#endif