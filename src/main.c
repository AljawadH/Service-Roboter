#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
<<<<<<< HEAD
#include "ev3_port.h"

=======
>>>>>>> 7432860de3975a54746a0cb07ca72f35b4ca6e3c
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

<<<<<<< HEAD
    motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTA, OUTPUT_A);
=======
>>>>>>> 7432860de3975a54746a0cb07ca72f35b4ca6e3c

      pen_t* pen = create_pen(LEGO_EV3_M_MOTOR);
      test_pen(pen);

      motor_t* left_m = create_motor(LEGO_EV3_L_MOTOR, OUTA);
      //motor_t* right_m = create_motor(LEGO_EV3_L_MOTOR, OUTD);

      remove_motor(left_m);
      //remove_motor(right_m);

<<<<<<< HEAD
    remove_pen(pen);
    remove_motor(left_m);


=======
      remove_pen(pen);
>>>>>>> 7432860de3975a54746a0cb07ca72f35b4ca6e3c


    return 0;
}
