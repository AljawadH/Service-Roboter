#ifndef PEN_H
#define PEN_H

#include "ev3.h"
#include "ev3_tacho.h"


typedef struct {
    
    uint8_t sn;
    int max_speed;
    bool isup;
    
} pen_t;


pen_t* create_pen(INX_T type);

void remove_pen(pen_t* pen);

void test_pen(pen_t* pen);

void move_pen_down(pen_t* pen);

void move_pen_up(pen_t* pen);



#endif