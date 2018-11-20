
#include "ev3.h"
#include "ev3_tacho.h"


typedef struct {

    uint8_t sn;
    int max_speed;
} motor_t;


motor_t* create_motor(INX_T type, uint8_t port, uint8_t extport);

void remove_motor(motor_t* motor);

//void move(motor_t* left_m, motor_t* right_m, int8_t dist);
void move ( int distance ) ; 

void rotate(motor_t* left, motor_t* right, int16_t deg);

void curve(motor_t* left, motor_t* right, uint8_t rad, int16_t deg);