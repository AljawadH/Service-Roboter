#include <stdio.h>
#include <brick.h>
#include <tacho.h>

#define SPEED_CIRCULAR  25

#define MOTOR_LEFT OUTA
#define MOTOR_RIGHT OUTB
#define MOTOR_BOTH ( MOTOR_LEFT | MOTOR_RIGHT ) 



// gerade Linie
void moveForward(int distance){
	uint8_t sn;
	if (tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE_NONE)){
		int max_speed=tacho_get_max_speed(MOTOR_RIGHT,0);
		tacho_reset(MOTOR_BOTH);
		} 
		else 
			printf ("Motors not found\n"); 
		
		int time = distance / max_speed;
		
			if ( ev3_search_tacho( MOTOR_BOTH, &sn, 0 )) {
				set_tacho_stop_action_inx( sn, TACHO_COAST );
				set_tacho_speed_sp( sn, max_speed );
				set_tacho_time_sp( sn, time  );
				set_tacho_ramp_up_sp( sn, 2000 );
				set_tacho_ramp_down_sp( sn, 2000 );
				set_tacho_command_inx( sn, TACHO_RUN_TIMED );
				Sleep ( 100 ) ;
				}
	}
	
			
    
}

//nach links drehen um eigene Achse
void turnLeftOnPoint(int degree){
      tacho_set_speed_sp( MOTOR_LEFT, degree );
		tacho_set_speed_sp( MOTOR_RIGHT, -degree );
		tacho_run_forever( MOTOR_BOTH );
}

//nach rechts drehen um eigene Achse
void turnRightOnPoint(int degree){
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

