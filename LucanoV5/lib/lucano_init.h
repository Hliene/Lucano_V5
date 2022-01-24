#ifndef LUCANO_INIT_H
#define LUCANO_INIT_H

#include <Arduino.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE



//States 
#define IDLE                    1
#define HOOK_FALL_PROTECTION    2
#define READY_TO_START          3
#define WORK                    4

//Variabels



//Pins der Spare Stecker
#define Spare1_Pin2     45
#define Spare1_Pin3     47
#define Spare1_Pin4     44
#define Spare3_Pin5     46

#define Spare2_Pin2     49
#define Spare2_Pin3     51
#define Spare2_Pin4     53

#define Spare3_Pin2     48
#define Spare3_Pin3     52
#define Spare3_Pin4     50

//Pins für Stecker Schere
#define SCHERE_Pin2         40
#define SCHERE_Pin3         41
#define SCHERE_Pin4         42
#define SCHERE_Pin5         43


//INPUT Raspberry Pi LED+SUMMER
// Stecker = Spare2 
#define IN_LED_RED    digitalRead(Spare2_Pin2)            //Pin 2 Stecker 2
#define IN_LED_GREEN  digitalRead(Spare2_Pin3)            //Pin 3 Stecker 2
#define IN_SUMMER     digitalRead(Spare2_Pin4)            //PIN 4 Stecker 2

//INPUT RASPBERRY FAHRTRICHTUNG
//Stecker Spare 3
#define DRIVE_UP      digitalRead(Spare3_Pin2)            //Pin 2 Stecker 3
#define DRIVE_DOWN    digitalRead(Spare3_Pin3)            //Pin 3 Stecker 3

//INPUT Raspberry Hubsäule
#define HUB_UP        digitalRead(SCHERE_Pin2)
#define HUB_DOWN      digitalRead(SCHERE_Pin4)



//Prototypes
void init_lucano(void);

#endif
