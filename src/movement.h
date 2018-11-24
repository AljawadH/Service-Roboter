
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "ev3.h"
#include "ev3_tacho.h"
#include "pen.h"


typedef struct {

    uint8_t sn;
    int max_speed;
} motor_t;


motor_t* create_motor(INX_T type, uint8_t port);

void remove_motor(motor_t* motor);

void move(motor_t* left_m, motor_t* right_m, int dist);

void rotate(motor_t* left_m, motor_t* right_m, int deg);

void curve(motor_t* left_m, motor_t* right_m, uint8_t rad, int16_t deg);


#endif