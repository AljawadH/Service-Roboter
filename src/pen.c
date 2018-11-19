#include "pen.h"

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

#include <stdlib.h>
#include <stdio.h>

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

void move_pen_down() {

}

void move_pen_up() {

}

bool pen_up() {

    return 0;
}


void test_pen(pen_t* pen) {

    int buf;
    printf("test: pen tacho position=%d returned buffer value=%d\n", (int)get_tacho_position(pen->sn, &buf), buf);
    
}

