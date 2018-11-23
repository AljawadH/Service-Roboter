
#include "movement.h"

#include "ev3.h"
#include "ev3_tacho.h"
#include "ev3_port.h"
#include <stdlib.h>
#include <stdio.h>
#include "brick.h"
#include <unistd.h>

static const int MOVE_RAMP_UP = 200;
static const int MOVE_RAMP_DOWN = 200;

motor_t* create_motor(INX_T type, uint8_t port) {

    if(ev3_tacho_init() == -1) {
        printf("motor could not be created -- no tacho motor found\n");
        return NULL;
    }

    motor_t* motor = (motor_t*) malloc(sizeof(motor_t));


    //TODO: search extended port number
    ev3_search_tacho_plugged_in(port, EXT_PORT__NONE_, &(motor->sn), 0);
    get_tacho_max_speed(motor->sn, &(motor->max_speed));

    printf("motor created\n");

    printf("motor initialized\n");

    return motor;
}    

void remove_motor(motor_t* motor) {
    free(motor);
}

void move(motor_t* left_m, motor_t* right_m, int dist) {

    set_tacho_position_sp(left_m->sn, -dist);
    set_tacho_speed_sp(left_m->sn, left_m->max_speed / 15);
    set_tacho_ramp_up_sp(left_m->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(left_m->sn, MOVE_RAMP_DOWN);

    set_tacho_position_sp(right_m->sn, -dist);
    set_tacho_speed_sp(right_m->sn, right_m->max_speed / 15);
    set_tacho_ramp_up_sp(right_m->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(right_m->sn, MOVE_RAMP_DOWN);


    set_tacho_command_inx(left_m->sn, TACHO_RUN_TO_REL_POS);
    set_tacho_command_inx(right_m->sn, TACHO_RUN_TO_REL_POS);


    FLAGS_T flag_left;
    FLAGS_T flag_right;
    do {
        get_tacho_state_flags(left_m->sn, &flag_left);
        get_tacho_state_flags(right_m->sn, &flag_right);
        if(flag_left == TACHO_RAMPING) {
            set_tacho_command_inx(left_m->sn, TACHO_STOP);
        }
        if(flag_right == TACHO_RAMPING) {
            set_tacho_command_inx(right_m->sn, TACHO_STOP);
        }
    } while (flag_left || flag_right);

    printf("moved rel distance=%d\n", dist);
}


void rotate(motor_t* left_m, motor_t* right_m, int deg) {

    set_tacho_position_sp(left_m->sn, deg);
    set_tacho_speed_sp(left_m->sn, left_m->max_speed / 15);
    set_tacho_ramp_up_sp(left_m->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(left_m->sn, MOVE_RAMP_DOWN);

    set_tacho_position_sp(right_m->sn, -deg);
    set_tacho_speed_sp(right_m->sn, right_m->max_speed / 15);
    set_tacho_ramp_up_sp(right_m->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(right_m->sn, MOVE_RAMP_DOWN);


    set_tacho_command_inx(left_m->sn, TACHO_RUN_TO_REL_POS);
    set_tacho_command_inx(right_m->sn, TACHO_RUN_TO_REL_POS);


    FLAGS_T flag_left;
    FLAGS_T flag_right;
    do {
        get_tacho_state_flags(left_m->sn, &flag_left);
        get_tacho_state_flags(right_m->sn, &flag_right);
        if(flag_left == TACHO_RAMPING) {
            set_tacho_command_inx(left_m->sn, TACHO_STOP);
        }
        if(flag_right == TACHO_RAMPING) {
            set_tacho_command_inx(right_m->sn, TACHO_STOP);
        }
    } while (flag_left || flag_right);

    printf("roteted degrees=%d\n", deg);

    
}

void curveLeft(motor_t* left, motor_t* right, uint8_t rad, int16_t deg) {
    float nullRad= 10.2;

    if(rad<=0){return;}
    if (rad<nullRad){
        float linkesRad = (rad-nullRad) * -1;
        float rechtesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, (left->max_speed/50 * linkesRad) * -1);
        set_tacho_speed_sp(right->sn, right->max_speed/50 * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }else if(rad>nullRad){
        float linkesRad = rad-nullRad;
        float rechtesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/50 * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/50 * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }
}

void curveRight(motor_t* left, motor_t* right, uint8_t rad, int16_t deg) {
    float nullRad= 10.2;

    if(rad<=0){return;}
    if (rad<nullRad){
        float rechtesRad = (rad-nullRad);
        float linkesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/50 * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/50 * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }else if(rad>nullRad){
        float rechtesRad = rad-nullRad;
        float linkesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/50 * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/50 * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }
}