#ifndef GYRO_CTRL
#define GYRO_CTRL

#include "ev3.h"


#include "brick.h"
#include "ev3_sensor.h"


typedef struct {
    
    uint8_t sn;
    int start_deg;
    
} gyro_t;


gyro_t* create_gyro();
void remove_gyro(gyro_t *gyro);

int read_degree(gyro_t *gyro); 

void gyro_reset(gyro_t* gyro);



#endif