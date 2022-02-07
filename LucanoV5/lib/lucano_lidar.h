#ifndef LUCANO_LIDAR_H
#define LUCANO_LIDAR_H

#include <Arduino.h>

//      Prototypes
void init_lidar1(void);
void getTFminiData1(int* distance, int* strength);
void init_I2C_lidar();
int getTFminiDataI2C(void);

#endif
