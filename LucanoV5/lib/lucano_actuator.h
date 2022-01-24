#ifndef LUCANO_ACTUATOR_H
#define LUCANO_ACTUATOR_H

#include <Arduino.h>

#define DIRECTION1  22
#define DIRECTION2  23

#define PWM1        2
#define PWM2        3
#define PWM3        4
#define PWM4        5
#define PWM5        6
#define PWM6        7

#define ANALOG      150

#define FB1         A11
#define FB2         A10
#define FB3         A9
#define FB4         A8
#define FB5         A7
#define FB6         A7

#define SEN1A       A0
#define SEN1B       A1
#define SEN2A       A2
#define SEN2B       A3
#define SEN3A       A4
#define SEN3B       A5

//Prototypes
void init_actuator(void);
uint8_t _actuator1(uint16_t extent);
uint8_t _actuator2(uint16_t extent);

#endif
