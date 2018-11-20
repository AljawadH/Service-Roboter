
#include "movement.h"

#include "ev3.h"
#include "ev3_tacho.h"
#include "ev3_port.h"
#include <stdlib.h>
#include <stdio.h>


static const int MOVE_RAMP_UP = 200;
static const int MOVE_RAMP_DOWN = 200;

#define MOTOR_LEFT OUTA
#define MOTOR_RIGHT OUTB
#define MOTOR_BOTH ( MOTOR_LEFT | MOTOR_RIGHT ) 

motor_t* create_motor(INX_T type, uint8_t port) {

    if(ev3_tacho_init() == -1) {
        printf("motor could not be created -- no tacho motor found\n");
        return NULL;
    }

    motor_t* motor = (motor_t*) malloc(sizeof(motor_t));


    //TODO: search extended port number
    ev3_search_tacho_plugged_in(port, MS_NXTMMX_OUT_PORT_TACHO_MOTOR, &(motor->sn), 0);
    get_tacho_max_speed(motor->sn, &(motor->max_speed));

    printf("motor created\n");

    set_tacho_position_sp(motor->sn, 0);
    set_tacho_ramp_up_sp(motor->sn, MOVE_RAMP_UP);
    set_tacho_ramp_down_sp(motor->sn, MOVE_RAMP_DOWN);
    set_tacho_command_inx(motor->sn, TACHO_RUN_TO_ABS_POS);

    FLAGS_T flag;
    do {
        get_tacho_state_flags(motor->sn, &flag);
        if(flag == TACHO_RAMPING) {
            set_tacho_command_inx(motor->sn, TACHO_STOP);
        }
    } while (flag);

    printf("motor initialized and set to 0\n");

    return NULL;
}    


void remove_motor(motor_t* motor) {
    free(motor);
}

//void move(motor_t* left_m, motor_t* right_m, int8_t dist) {
void move(int distance ) {
		uint8_t sn;
	if (tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE_NONE)){
		int max_speed=tacho_get_max_speed(MOTOR_RIGHT,0);
		tacho_reset(MOTOR_BOTH);
		} 
		else 
			printf ("Motors not found\n"); 
		
		int time = distance / max_speed;
		
			if ( ev3_search_tacho( MOTOR_BOTH, &sn, 0 )) {
				set_tacho_stop_action_inx( sn, TACHO_COAST );
				set_tacho_speed_sp( sn, max_speed );
				set_tacho_time_sp( sn, time  );
				set_tacho_ramp_up_sp( sn, 200 );
				set_tacho_ramp_down_sp( sn, 200 );
				set_tacho_command_inx( sn, TACHO_RUN_TIMED );
				Sleep ( 100 ) ;
				}
	}
	
			

}

void rotate(motor_t* left, motor_t* right, int16_t deg) {
    
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