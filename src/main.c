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

void kopfForm(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){

    const float curveDegree = 175.25;
    const float headHight = 12;

    curveLeft(left_m,right_m,8*factor,curveDegree);
    usleep(2000000); 
    move_pen_down(pen); 
    move(left_m,right_m,headHight*factor);
    usleep(2000000); 
    move_pen_down(pen); 
    curveLeft(left_m,right_m,8 * factor,curveDegree);
    usleep(2000000); 
    move_pen_down(pen); 
    move(left_m,right_m,headHight*factor);

}



void drawEyes(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){

    const float eyeDegree = 357;
    const float eyeRadius = 3.925;
    const float turnLeft = 90;

    move_pen_up(pen);
    move(left_m,right_m,-3.5*factor);
    usleep(2000000); 
    move_pen_down(pen);
    curveLeft(left_m,right_m,eyeRadius*factor,eyeDegree);
    usleep(2000000); 
    move_pen_up(pen);
    rotate_left(left_m,right_m,turnLeft);
    usleep(2000000);
    move(left_m,right_m,eyeRadius*factor);
    move_pen_down(pen);
    usleep(2000000); //dont remove
    move_pen_up(pen);
    usleep(2000000);
    move(left_m,right_m,eyeRadius*2*factor + 1);//TODO:
    usleep(2000000);
    move_pen_down(pen);
    usleep(2000000); //dont remove
    move_pen_up(pen);
    move(left_m,right_m,eyeRadius*factor);
    usleep(2000000);
    rotate_left(left_m,right_m,turnLeft);
    usleep(2000000);
    move_pen_down(pen);
    curveLeft(left_m,right_m,eyeRadius*factor,eyeDegree);






}





void drawFace(int factor, motor_t* left_m, motor_t* right_m, pen_t* pen){

    //pixel/700 * 35
    
    

    //TODO: aus der mitter fahren

    kopfForm(factor,left_m,right_m,pen);
    drawEyes(factor,left_m,right_m,pen);

    
    


    // curveLeft(left_m,right_m,1.25*factor,170);  //Auge huckel
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,90);
    // usleep(2000000); 
    // move_pen_down(pen);   
    // curveLeft(left_m,right_m,8*factor,180);   //oben Kopf
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,90);
    // usleep(2000000);
    // move_pen_down(pen);
    // curveLeft(left_m,right_m,1.25*factor,170);  //Auge huckel
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,105);
    // usleep(2000000);
    // move_pen_down(pen);
    // curveLeft(left_m,right_m,3.75*factor,380); //Auge
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,15);
    // usleep(2000000);
    // move_pen_down(pen);
    // move(left_m,right_m,2.25*factor);  //gerade unter Auge
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,90);
    // usleep(2000000);
    // move_pen_down(pen);
    // curveLeft(left_m,right_m,1.75*factor,170); //Ohr links
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_right(left_m,right_m,90);
    // usleep(2000000);
    // move_pen_down(pen);
    // // move(left_m,right_m,1.25*factor);   //Strich Ohr
    // // usleep(2000000);
    // // move_pen_down(pen);
    // rotate_left(left_m,right_m,180);
    // usleep(2000000);
    // move_pen_down(pen);
    // // move(left_m,right_m,1.75*factor);  //Strich Ohr-Mund
    // // usleep(2000000);
    // // move_pen_down(pen);
    // curveLeft(left_m,right_m,8*factor,180);
    // usleep(2000000);
    // move_pen_down(pen);
    // move(left_m,right_m,3.5*factor);   //Strich mund
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_left(right_m,left_m,180);
    // usleep(2000000);
    // move_pen_down(pen);
    // move(left_m,right_m,2.5*factor);
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_left(left_m,right_m,90);
    // usleep(2000000);
    // move_pen_down(pen);
    // curveLeft(left_m,right_m,1.75*factor,170);   //Ohr rechts
    // usleep(2000000);
    // move_pen_down(pen);
    // rotate_left(left_m,right_m,15);
    // usleep(2000000);
    // move_pen_down(pen);
    // curveLeft(left_m,right_m,3.75*factor,380); //Auge   




    


}


int main(){

    gyro_t* gyro = create_gyro();

    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_D);
    motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTPUT_A);

    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    
    

    //test_square(2, left_m, right_m, pen, gyro);
    move_pen_down(pen);
    drawFace(1,left_m,right_m,pen);
    

    // move_pen_up(pen);


    remove_pen(pen);
    remove_motor(left_m);
    remove_motor(right_m);

    remove_gyro(gyro);

    return 0;
}
