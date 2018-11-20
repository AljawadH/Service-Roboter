#include "pen.h"

#include "ev3.h"
#include "ev3_tacho.h"

#include <stdlib.h>
#include <stdio.h>


static const int PEN_DOWN_POSITION = -145;
static const int PEN_UP_POSITION = -110;

static const int PEN_MOVE_SPEED = 15;

static const int PEN_RAMP_UP = 2000;
static const int PEN_RAMP_DOWN = 2000;

pen_t* create_pen(INX_T type) {

    if(ev3_tacho_init() == -1) {
        printf("pen could not be created -- no tacho motor found\n");
        return NULL;
    }

    pen_t* pen = (pen_t*)malloc(sizeof(pen_t));

    ev3_search_tacho(type, &(pen->sn), 0);
    get_tacho_max_speed(pen->sn, &(pen->max_speed));

    printf("pen created\n");

    move_pen_up(pen);
    pen->isup = true;


    printf("pen initialized\n");
    return pen;
}

void remove_pen(pen_t* pen) {
    printf("pen removed\n");
    free(pen);
}

void print_pen_position(pen_t* pen) {
    
    int buff;
    get_tacho_position_sp(pen->sn, &buff);
    printf("pen position=%d\n", buff);
}


void move_pen_down(pen_t* pen) {

    set_tacho_speed_sp(pen->sn, pen->max_speed / PEN_MOVE_SPEED);
    set_tacho_position_sp(pen->sn, PEN_DOWN_POSITION);
    set_tacho_ramp_up_sp(pen->sn, PEN_RAMP_UP);
    set_tacho_ramp_down_sp(pen->sn, PEN_RAMP_DOWN);

    set_tacho_command_inx(pen->sn, TACHO_RUN_TO_ABS_POS);

    pen->isup = false;

    FLAGS_T flag;
    do {
        get_tacho_state_flags(pen->sn, &flag);
        if(flag == TACHO_RAMPING) {
            set_tacho_command_inx(pen->sn, TACHO_STOP);
        }
    } while (flag);

    printf("PEN DOWN\n");
    print_pen_position(pen);


}

void move_pen_up(pen_t* pen) {

    set_tacho_speed_sp(pen->sn, pen->max_speed / PEN_MOVE_SPEED);
    set_tacho_position_sp(pen->sn, PEN_UP_POSITION);
    set_tacho_ramp_up_sp(pen->sn, PEN_RAMP_UP);
    set_tacho_ramp_down_sp(pen->sn, PEN_RAMP_DOWN);

    set_tacho_command_inx(pen->sn, TACHO_RUN_TO_ABS_POS);

    pen->isup = true;

    FLAGS_T flag;
    do {
        get_tacho_state_flags(pen->sn, &flag);
        if(flag == TACHO_RAMPING) {
            set_tacho_command_inx(pen->sn, TACHO_STOP);
        }
    } while (flag);

    printf("PEN UP\n");
    print_pen_position(pen);
    
}


void test_pen(pen_t* pen) {

    move_pen_down(pen);

    move_pen_up(pen);
    
}

