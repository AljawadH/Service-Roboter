#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_port.h"

#include "brick.h"
#include "pen.h"
#include "movement.h"




int main(){

    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_A);
    motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_D);

    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    //move_pen_down(pen);

    //rotate(left_m, right_m, 30);
    move(left_m, right_m, 500);

    rotate(left_m, right_m, -300);


    //move_pen_up(pen);

    remove_pen(pen);
    remove_motor(left_m);
    remove_motor(right_m);


    return 0;
}
