
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "ev3.h"
#include "ev3_tacho.h"
#include "pen.h"
#include "gyro_ctrl.h"


typedef struct {

    uint8_t sn;
    int max_speed;
} motor_t;


motor_t* create_motor(INX_T type, uint8_t port);

void remove_motor(motor_t* motor);

void move(motor_t* left_m, motor_t* right_m, int dist);

void rotate_right(motor_t* left_m, motor_t* right_m, int deg);

void rotate_left(motor_t* left_m, motor_t* right_m, int deg);

void curveLeft(motor_t* left_m, motor_t* right_m, int rad, int deg);
void curveRight(motor_t* left_m, motor_t* right_m, int rad, int deg);


#endif