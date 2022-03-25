#ifndef LUCANO_DRIVE_H
#define LUCANO_DRIVE_H

#include <Arduino.h>

//      Stecker für Finger Antrieb
#define PWM_FL        8               //PWM Finger Links
#define PWM_FML       9               //PWM Finger Mitte Links
#define PWM_FMR       10              //PWM Finger Mitte Rechts
#define PWM_FR        11              //PWM Finger Rechts

#define DIR_FL        24              //direction Finger Links
#define DIR_FML       25              //direction Finger Mitte Links
#define DIR_FMR       27              //direction Finger Mitte Rechts
#define DIR_FR        26              //direction Finger Rechts

#define SPARE_FL  35              //Sparepin Finger Links
#define SPARE_FML 36              //Sparepin Finger Mitte Links
#define SPARE_FMR 37              //Sparepin Finger Mitte Rechts
#define SPARE_FR  38              //Sparepin Finger Rechts

#define ERROR_FL    digitalRead(SPARE_FL)     //Fehler Antrieb Finger Links
#define ERROR_FML   digitalRead(SPARE_FML)    //Fehler Antrieb Finger Links
#define ERROR_FMR   digitalRead(SPARE_FMR)    //Fehler Antrieb Finger Links
#define ERROR_FR    digitalRead(SPARE_FR)     //Fehler Antrieb Finger Links

#define CURRENT_FR    A0
#define CURRENT_FMR   A1
#define CURRENT_FML   A2
#define CURRENT_FL    A3

#define AntriebSpeed  250             // 0-255 Antriebsgeschwindigkeit der Räder 

//      Prototypes
uint16_t _drive_UP(void);
void _drive_DOWN(void);
void _drive_STOP(void);
void init_drive(void);
void _attach_to_tree(void);
void _remove_from_tree(void);

#endif
