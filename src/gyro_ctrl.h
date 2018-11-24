#ifndef GYRO_CTRL
#define GYRO_CTRL


#include "ev3.h"

#include "brick.h"
#include "ev3_sensor.h"


typedef struct {
    
    uint8_t sn;
    bool isup;
    
} gyro_t;


gyro_t* create_gyro(INX_T type);
void remove_gyro(gyro_t *gyro);

int read_degree(gyro_t *gyro); 



#endif