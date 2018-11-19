#include <stdio.h>
#include "ev3.h"

#include "brick.h"
#include "pen.h"


// gerade Linie
void moveForward(int distance){
 
}
/*
//nach links drehen um eigene Achse
void turnLeftOnPoint(int degree)
{
   tacho_set_speed_sp( MOTOR_LEFT, degree );
   tacho_set_speed_sp( MOTOR_RIGHT, -degree );
   tacho_run_forever( MOTOR_BOTH );
}

//nach rechts drehen um eigene Achse
void turnRightOnPoint(int degree)
{
   tacho_set_speed_sp( MOTOR_RIGHT, degree );
   tacho_set_speed_sp( MOTOR_LEFT, -degree );
   tacho_run_forever( MOTOR_BOTH );    
}
*/
//Linkskurve
void curveLeft(int radius, int degree){
    
}

//Rechtskurve
void curveRight(int radius, int degree){
    
}


int main(){
    
    
    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);

    test_pen(pen);


    remove_pen(pen);


    //brick_init();




    //brick_uninit();
    return 0;
}
