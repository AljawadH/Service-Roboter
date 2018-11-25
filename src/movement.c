
#include "movement.h"

#include "ev3.h"
#include "ev3_tacho.h"
#include "ev3_port.h"
#include <stdlib.h>
#include <stdio.h>
#include "brick.h"
#include <unistd.h>
#include "pen.h"
#include "gyro_ctrl.h"

static const int MOVE_RAMP_UP = 200;
static const int MOVE_RAMP_DOWN = 200;

static const int POS_FACTOR = 33.5;
static const int MAX_SPEED_FACTOR = 5;

static const float ROT_POS_FACTOR = 5.17;



static const int MAX_ROT_DEG = 360;



motor_t* create_motor(INX_T type, uint8_t port) {

    if(ev3_tacho_init() == -1) {
        printf("motor could not be created -- no tacho motor found\n");
        return NULL;
    }

    motor_t* motor = (motor_t*) malloc(sizeof(motor_t));


    
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

    set_tacho_stop_action_inx(left_m->sn,TACHO_HOLD);
    set_tacho_stop_action_inx(right_m->sn,TACHO_HOLD);


    set_tacho_position_sp(left_m->sn, -dist * POS_FACTOR);
    set_tacho_speed_sp(left_m->sn, left_m->max_speed / MAX_SPEED_FACTOR);
    set_tacho_ramp_up_sp(left_m->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(left_m->sn, MOVE_RAMP_DOWN);

    set_tacho_position_sp(right_m->sn, -dist * POS_FACTOR);
    set_tacho_speed_sp(right_m->sn, right_m->max_speed / MAX_SPEED_FACTOR);
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


void rotate(motor_t* left_m, motor_t* right_m, int deg, gyro_t* gyro) {

    if(deg == 0) return;

    gyro_reset(gyro);

    if(deg > 0) {
        set_tacho_polarity_inx(right_m->sn, TACHO_INVERSED);
    }
    else if(deg < 0) {
        set_tacho_polarity_inx(left_m->sn, TACHO_INVERSED);

    }
    set_tacho_speed_sp(left_m->sn, (left_m->max_speed / MAX_SPEED_FACTOR));// * deg / MAX_ROT_DEG);
    set_tacho_speed_sp(right_m->sn, (right_m->max_speed / MAX_SPEED_FACTOR));// * deg / MAX_ROT_DEG);

    set_tacho_ramp_up_sp(left_m->sn, 0);
    set_tacho_ramp_up_sp(right_m->sn, 0);
    
    set_tacho_ramp_down_sp(left_m->sn, 0);
    set_tacho_ramp_down_sp(right_m->sn, 0);

    set_tacho_stop_action_inx(left_m->sn,TACHO_HOLD);
    set_tacho_stop_action_inx(right_m->sn,TACHO_HOLD);

    set_tacho_command_inx(left_m->sn, TACHO_RUN_FOREVER);
    set_tacho_command_inx(right_m->sn, TACHO_RUN_FOREVER);

    if(deg > 0) {

        
        int curr_deg = read_degree(gyro);
        
        while (curr_deg <= deg) {

            /*set_tacho_speed_sp(left_m->sn, (left_m->max_speed / MAX_SPEED_FACTOR) * ((deg - curr_deg) / MAX_ROT_DEG));
            set_tacho_command_inx(left_m->sn, TACHO_RUN_FOREVER);
            set_tacho_command_inx(right_m->sn, TACHO_RUN_FOREVER);*/
            printf("deg:%d\n",curr_deg);
            curr_deg = read_degree(gyro);
        }
        


    }
    else if(deg < 0) {

        int curr_deg = read_degree(gyro);
        
        while (curr_deg >= deg) {


            /*set_tacho_speed_sp(left_m->sn, (left_m->max_speed / MAX_SPEED_FACTOR) * ((deg - curr_deg) / MAX_ROT_DEG));
            set_tacho_command_inx(left_m->sn, TACHO_RUN_FOREVER);
            set_tacho_command_inx(right_m->sn, TACHO_RUN_FOREVER);*/

            curr_deg = read_degree(gyro);
            printf("deg:%d\n",curr_deg);
        }
        
    }

    set_tacho_command_inx(right_m->sn, TACHO_STOP);
    set_tacho_command_inx(left_m->sn, TACHO_STOP);

    set_tacho_polarity_inx(left_m->sn, TACHO_NORMAL);
    set_tacho_polarity_inx(right_m->sn, TACHO_NORMAL);
    

    printf("roteted degrees=%d\n", deg);

    
}

void rotate_right(motor_t* left_m, motor_t* right_m, int deg, gyro_t* gyro) {

    if(deg <= 0) {
        deg = -deg;
    }
    rotate(left_m, right_m, deg, gyro);

}

void rotate_left(motor_t* left_m, motor_t* right_m, int deg, gyro_t* gyro) {

    if(deg >= 0) deg = -deg;

    rotate(left_m, right_m, deg, gyro);
}

void curveLeft(motor_t* left, motor_t* right, uint8_t rad, int16_t deg) {
    int speedTeiler=20;
    float nullRad= 10.2;

    if(rad<=0){return;}
    if (rad<nullRad){
        float linkesRad = (rad-nullRad) * -1;
        float rechtesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, (left->max_speed/speedTeiler * linkesRad) * -1);
        set_tacho_speed_sp(right->sn, right->max_speed/speedTeiler * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }else if(rad>nullRad){
        float linkesRad = rad-nullRad;
        float rechtesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/speedTeiler * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/speedTeiler * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }
}

void curveRight(motor_t* left, motor_t* right, uint8_t rad, int16_t deg) {
    int speedTeiler=20;
    float nullRad= 10.2;

    if(rad<=0){return;}
    if (rad<nullRad){
        float rechtesRad = (rad-nullRad);
        float linkesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/speedTeiler * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/speedTeiler * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }else if(rad>nullRad){
        float rechtesRad = rad-nullRad;
        float linkesRad = rad + nullRad;
        set_tacho_speed_sp(left->sn, left->max_speed/speedTeiler * linkesRad);
        set_tacho_speed_sp(right->sn, right->max_speed/speedTeiler * rechtesRad);
        tacho_run_forever(left->sn);
        tacho_run_forever(right->sn);
        sleep(2000); //gyro abbruch TODO
        tacho_stop(left->sn);
        tacho_stop(right->sn);
    }
}