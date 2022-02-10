#ifndef LUCANO_LIFTING_COLUMN_H
#define LUCANO_LIFTING_COLUMN_H

#include <Arduino.h>

// Ausleger Schere
#define PWM_ASP           5                           //Ausleger Schere PWM 1
#define PWM_ASN           12                          //Ausleger Schere PWM 2
#define HS_CURRENT        A12                         //Motorstrom Ausleger Schere
#define ENDSTOP_HS_PIN    39                          //Endlagenschalter Ausleger Schere = NO
#define ENDSTOP_HS        digitalRead(ENDSTOP_HS_PIN)     //Ist Hubsäule eingefahren

#define LOOPS_REF_LIFTING_COLLUM    10

extern uint16_t ref_counter;



//Prototypes
void init_lifting_column(void);
uint8_t lift_column(void);
uint8_t retract_column(void);
uint8_t ref_column(void);

#endif
