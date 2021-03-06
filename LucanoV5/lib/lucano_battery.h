#ifndef LUCANO_BATTERY_H
#define LUCANO_BATTERY_H
#include <Arduino.h>


//Input baterie Value
#define     BAT_IN          A13                                 //analogpin zum Einlesen der Bateriespanunng

#define     BAT_MIN_VALE    430
#define     BAT_MAX_VALE    130

//Prototypes
void init_battery(void);
uint16_t read_battery(void);
uint16_t _battery(const char* page);

extern uint16_t old_baterie_value;


#endif