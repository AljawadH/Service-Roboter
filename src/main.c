#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"

#include "brick.h"



#include "pen.h"
#include "movement.h"


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




int main(){
    
    pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
    test_pen(pen);

    //motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTA);


    remove_pen(pen);
    //remove_motor(left_m);


    return 0;
}
