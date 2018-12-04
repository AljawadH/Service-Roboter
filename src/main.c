#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_port.h"
#include "brick.h"
#include "pen.h"
#include "movement.h"
#include "gyro_ctrl.h"
#include <unistd.h>



void test_square(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen) {

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

void kopfForm(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    const float curveDegree = 172.25;
    const float curveNotDrawn = 23;
    const float headHight = 12;
    const int sleepDuration = 0;

    curveLeft(left_m,right_m,8*factor,curveDegree);
    usleep(sleepDuration); 
    move_pen_down(pen); 
    move(left_m,right_m,headHight*factor);
    usleep(sleepDuration); 
    move_pen_down(pen); 
    move_pen_up(pen);
    curveLeft(left_m,right_m,8 * factor,curveNotDrawn);
    move_pen_down(pen);
    curveLeft(left_m,right_m,8 * factor,curveDegree-2*curveNotDrawn);
     move_pen_up(pen);
    curveLeft(left_m,right_m,8 * factor,curveNotDrawn);
    usleep(sleepDuration); 
    move_pen_down(pen); 
    move(left_m,right_m,headHight*factor);
}



void drawEyes(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    const float eyeDegree = 350;
    const float eyeRadius = 3.925;
    const float turnLeft = 80;
    const int sleepDuration = 0;

    move_pen_up(pen);
    move(left_m,right_m,-5*factor);
    usleep(sleepDuration); 
    move_pen_down(pen);
    curveLeft(left_m,right_m,eyeRadius*factor,eyeDegree);
    usleep(sleepDuration); 
    move_pen_up(pen);
    rotate_left(left_m,right_m,turnLeft);
    usleep(sleepDuration);
    move(left_m,right_m,eyeRadius*factor);
    move_pen_down(pen);
    usleep(2000000); //dont remove
    move_pen_up(pen);
    usleep(sleepDuration);
    move(left_m,right_m,eyeRadius*2*factor + 1);//TODO:
    usleep(sleepDuration);
    move_pen_down(pen);
    usleep(2000000); //dont remove
    move_pen_up(pen);
    move(left_m,right_m,eyeRadius*factor);
    usleep(sleepDuration);
    rotate_left(left_m,right_m,turnLeft);
    usleep(sleepDuration);
    move_pen_down(pen);
    curveLeft(left_m,right_m,eyeRadius*factor,eyeDegree);
}

void drawNose(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    const float gerade = 6.5;
    const int sleepDuration = 0;

    move_pen_up(pen);
    move(left_m,right_m,3*factor);
    usleep(sleepDuration);
    rotate_left(left_m,right_m,90);
    usleep(sleepDuration);
    move(left_m,right_m,gerade*factor);
    usleep(sleepDuration);
    rotate_right(left_m,right_m, 150);
    usleep(sleepDuration);
    move_pen_down(pen);
    usleep(sleepDuration);
    curveLeft(left_m,right_m,1*factor,300);
}

void drawMouth(int factor,motor_t* left_m, motor_t* right_m, pen_t* pen){
    const int sleepDuration = 0;
    const float mouthSidesRad = 5;
    const float mouthTopRad = 20;

    move_pen_up(pen);
    curveLeft(left_m,right_m,1*factor,210);
    usleep(sleepDuration);
    rotate_right(left_m,right_m,105);
    move(left_m,right_m,2);
    rotate_right(left_m,right_m,100);
    usleep(sleepDuration);
    move_pen_down(pen);
    curveLeft(left_m,right_m,mouthTopRad,20);
    usleep(sleepDuration);
    curveLeft(left_m,right_m,mouthSidesRad,140);
    usleep(sleepDuration);
    curveLeft(left_m,right_m,mouthTopRad,40);
    usleep(sleepDuration);
    curveLeft(left_m,right_m,mouthSidesRad,140);
    usleep(sleepDuration);
    curveLeft(left_m,right_m,mouthTopRad,19);
}

void drawEars(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    static int sleepDuration= 2000000;

    move_pen_up(pen);
    rotate_right(left_m,right_m,100);
    usleep(sleepDuration);
    move(left_m,right_m,4);
    usleep(sleepDuration);
    rotate_left(left_m,right_m,90);
    usleep(sleepDuration);
    move(left_m,right_m,3.925*2-0.5);
    usleep(sleepDuration);
    rotate_right(left_m,right_m,35);
    usleep(sleepDuration);
    move_pen_down(pen);
    curveLeft(left_m,right_m,1,250);
    move_pen_up(pen);
    usleep(sleepDuration);
    rotate_right(left_m,right_m,35);
    usleep(sleepDuration);
    move(left_m,right_m,(3.925*2)*2);
    usleep(sleepDuration);
    rotate_right(left_m,right_m,35);
    usleep(sleepDuration);
    move_pen_down(pen);
    curveLeft(left_m,right_m,1,250);
    move_pen_up(pen);
}





void drawFace(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){
    //pixel/700 * 35
    //TODO: aus der mitter fahren
    kopfForm(factor,left_m,right_m,pen);
    drawEyes(factor,left_m,right_m,pen);
    drawNose(factor,left_m,right_m,pen);
    drawMouth(factor,left_m,right_m,pen);
    // drawEars(factor,left_m,right_m,pen);
}


int main(){
    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_D);
    motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_A);
    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    
    

    //test_square(2, left_m, right_m, pen, gyro);
    move_pen_down(pen);
    drawFace(1,left_m,right_m,pen);
    //test_square(1, left_m, right_m, pen);
    // move_pen_up(pen);

    remove_pen(pen);
    remove_motor(left_m);
    remove_motor(right_m);

    return 0;
}
