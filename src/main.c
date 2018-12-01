#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_port.h"

#include "brick.h"
#include "pen.h"
#include "movement.h"
#include "gyro_ctrl.h"
#include <unistd.h>



void test_square(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen, gyro_t* gyro) {

    move_pen_down(pen);

    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90);
    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90);
    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90);
    move(left_m, right_m, 5 * factor);

    move_pen_up(pen);
    
}

void drawFace(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    
}


int main(){

    gyro_t* gyro = create_gyro();

    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_D);
    motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_A);

    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    
    

    //test_square(2, left_m, right_m, pen, gyro);
    move_pen_down(pen);
    curve(left_m, right_m, 5, 360);
     curve(left_m, right_m, 12, 360);
    // move_pen_up(pen);


    remove_pen(pen);
    remove_motor(left_m);
    remove_motor(right_m);

    remove_gyro(gyro);

    return 0;
}
