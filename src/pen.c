#include "pen.h"

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

pen_t* create_pen(INX_T type) {

    if(ev3_tacho_init() == -1) {
        printf("pen could not be created -- no tacho motor found\n");
        return NULL;
    }

    pen_t* pen = (pen_t*)malloc(sizeof(pen_t));

    ev3_search_tacho(type, &(pen->sn), 0);
    get_tacho_max_speed(pen->sn, &(pen->max_speed));


    printf("pen created\n");
    return pen;
}

void remove_pen(pen_t* pen) {

    free(pen);
}

void move_pen_down(pen_t* pen) {

    set_tacho_ramp_up_sp(pen->sn, 0);
    set_tacho_ramp_down_sp(pen->sn, 0);

    set_tacho_speed_sp(pen->sn, 200);

    set_tacho_position_sp(pen->sn, 50);
    
    set_tacho_command_inx(pen->sn, TACHO_RUN_TO_REL_POS);

    usleep(1000);

}

void move_pen_up(pen_t* pen) {

    set_tacho_ramp_up_sp(pen->sn, 0);
    set_tacho_ramp_down_sp(pen->sn, 0);

    set_tacho_speed_sp(pen->sn, 200);

    set_tacho_position_sp(pen->sn, 50);
    
    set_tacho_command_inx(pen->sn, TACHO_RUN_TO_REL_POS);

    usleep(1000);

}

bool pen_up() {

    return 0;
}


void test_pen(pen_t* pen) {

    int buf;
    get_tacho_position_sp(pen->sn, &buf);
    printf("test: pen tacho position=%d max_speed=%d\n", buf, pen->max_speed);

    move_pen_up(pen);

    move_pen_down(pen);

    
}

