#include "..\lib\led_summer.h"
#include <Arduino.h>


/*****************************************************************************
 * Function name:     init_ledSummer
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs die Status LEDs und dem Summer
 * 
 * Stecker:           LED_Summer
 *                    Red LED     = Pin 1
 *                    GND         = Pin2
 *                    Green LED   = Pin 3
 *                    Summer      = Pin 4+5
 *                    
 *                    
 * Output pins:       D33 = Green LED
 *                    D32 = Red LED
 *                    D34 = Summer
 *****************************************************************************/
void init_ledSummer(void){
  
  // Status LED und Summer  
  pinMode(REDLED,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  pinMode(SUMMER,OUTPUT);
  digitalWrite(REDLED,LOW);
  digitalWrite(SUMMER,LOW);
  digitalWrite(GREENLED,LOW);
}
