#ifndef LUCANO_LIDAR_H
#define LUCANO_LIDAR_H

#include <Arduino.h>

//      Prototypes
void init_lidar1(void);
void getTF_High_Data(uint16_t* distance, uint16_t* strength);
void init_I2C_lidar();
int getTFminiDataI2C(void);

#endif
