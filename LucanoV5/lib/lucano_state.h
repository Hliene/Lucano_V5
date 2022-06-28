#ifndef LUCANO_STATE_H
#define LUCANO_STATE_H

#include <Arduino.h>

//Define
#define MIN_DELCLIMBING_HEIGT   0
#define MAX_DELCLIMBING_HEIGT   12

#define DIFF_HEIGT_SISSOR       40

#define cm2m                    100

#define DRIVE_BACK_HEIGHT       80    

#define DEFALT_BAT_VAL          100




//States 
#define IDLE                    1
#define ATTACH_TO_TREE          2
#define HOOK_FALL_PROTECTION    3
#define READY_TO_START          4
#define WORK                    5
#define DRIVE_BACK              6
#define FINISHED                7
#define REMOTE_CONTROL          9
#define BATTERIE_EMPTY          10
#define REMOVE_FROM_TREE        11         


// Defines for states
#define BLINK_FREQ              0b0100000


//Variabels


//    Prototypes 
uint16_t idle(void);
uint16_t attach_to_tree(void);
uint16_t remove_from_tree(void);
uint16_t hook_fall_protection(void);
uint16_t work(void);
uint16_t ready_to_start(void);
uint16_t remote_control(void);
uint16_t drive_back(void);
uint16_t finished(void);

#endif