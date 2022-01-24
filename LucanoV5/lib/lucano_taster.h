#ifndef LUCANO_TASTER_H
#define LUCANO_TASTER_H

#include <Arduino.h>

#define BUTTOM_1      28
#define BUTTOM_2      29
#define BUTTOM_3      30
#define BUTTOM_4      31

#define BUTTOM_LOOPs  4096



//    Prototypes 
void init_Buttons(void);
uint8_t start_buttom(void);
uint8_t confirmation_buttom(void);
uint8_t plus_buttom(void);
uint8_t minus_buttom(void);


#endif
