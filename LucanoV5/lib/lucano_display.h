#ifndef LUCANO_DISPLAY_H
#define LUCANO_DISPLAY_H

#include <Arduino.h>






//    Prototypes 
void init_Display(void);
void Display_Page(const char* page);
void Display_delclimbing_height(uint16_t delclimbing_height, const char* page);
void Display_baterie_value(uint16_t baterie_value, const char* page);
uint16_t _battery(void);
void page4_text(const char* text1, const char* text2, const char* text3);

#endif