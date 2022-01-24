#ifndef LUCANO_DISPLAY_H
#define LUCANO_DISPLAY_H

#include <Arduino.h>






//    Prototypes 
void init_Display(void);
void Display_Page_0(void);
void Display_Page_1(void);
void Display_delclimbing_height(uint16_t delclimbing_height);
void Display_baterie_value(uint16_t baterie_value);

#endif