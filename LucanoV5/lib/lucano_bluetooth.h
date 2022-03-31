#ifndef INIT_BLUETOOTH_H
#define INIT_BLUETOOTH_H

#include <Arduino.h>

#define     DRIVE_UP        1
#define     DRIVE_DOWN      2
#define     DRIVE_STOP      3

//bool    stringComplete  = false;        // whether the string is complete



void init_bluetooth(void);
uint16_t _readSerial(void);
uint16_t _read_Bluetooth(void);




#endif