#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
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

    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTA, OUTPUT_A);

      pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
      test_pen(pen);

      motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTA);
      //motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTD);

      remove_motor(left_m);
      //remove_motor(right_m);

    remove_pen(pen);


    return 0;
}
