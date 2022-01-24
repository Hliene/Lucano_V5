#ifndef LUCANO_STATE_H
#define LUCANO_STATE_H

#include <Arduino.h>

//Define
#define MIN_DELCLIMBING_HEIGT 0
#define MAX_DELCLIMBING_HEIGT 12


//States 
#define IDLE                    1
#define HOOK_FALL_PROTECTION    2
#define READY_TO_START          3
#define WORK                    4

//Variabels


//    Prototypes 
uint16_t idle(void);
uint16_t hook_fall_protection(void);
uint16_t work(void);
uint16_t ready_to_start(void);

#endif