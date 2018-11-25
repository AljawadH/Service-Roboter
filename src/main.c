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

    //move_pen_down(pen);

    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90, gyro);
    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90, gyro);
    move(left_m, right_m, 5 * factor);
    usleep(100000);
    rotate_right(left_m, right_m, 90, gyro);
    move(left_m, right_m, 5 * factor);

    //move_pen_up(pen);
    
}


int main(){

    gyro_t* gyro = create_gyro();

    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_A);
    motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_D);

    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    
    //move_pen_down(pen);
    

    

    //test_square(2, left_m, right_m, pen, gyro);

    //move(left_m, right_m, 22);

    /*rotate_right(left_m, right_m, 360, gyro);

    usleep(1500000);

    rotate_left(left_m, right_m, 90, gyro);
    rotate_left(left_m, right_m, 90, gyro);
    rotate_left(left_m, right_m, 90, gyro);
    rotate_left(left_m, right_m, 90, gyro);

    usleep(1500000);

    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);
    rotate_left(left_m, right_m, 45, gyro);*/
    


    remove_pen(pen);
    remove_motor(left_m);
    remove_motor(right_m);

    remove_gyro(gyro);

    return 0;
}
