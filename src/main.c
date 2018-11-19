#include <stdio.h>
#include <brick.h>

#define SPEED_CIRCULAR  25

#define MOTOR_LEFT OUTA
#define MOTOR_LEFT OUTB
#define MOTOR_BOTH ( MOTOR_LEFT | MOTOR_RIGHT )


// gerade Linie
void moveForward(int distance){
 
}

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

//Linkskurve
void curveLeft(int radius, int degree){
    
}

//Rechtskurve
void curveRight(int radius, int degree){
    
}


int main(){
    
    brick_init();
    //code
    
    
    
    //code ende
    brick_uninit();
    return 0;
}
