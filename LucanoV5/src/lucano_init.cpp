#include "..\lib\lucano_init.h"

#include <Arduino.h>




/*****************************************************************************
 * Function name:     init_lucano
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs
 * 
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void init_lucano(void){

  // put your setup code here, to run once:
  Serial.begin(250000);




  
  // Konfiguration der Timer Register
  TCCR0B = ((TCCR0B & 0b11111000) | 0x03);        //Timer 0 Teiler 64
  TCCR3B = ((TCCR3B & 0b11111000) | 0x01);        //Timer 3 Teiler 1
  TCCR1B = ((TCCR1B & 0b11111000) | 0x02);        //Timer 1 Teiler 8
  //TCCR2B = ((TCCR1B & 0b11111000) | 0x02);        //Timer 1 Teiler 8
  
  

    // Konfiguration der Timer Register
  //TCCR0B = TCCR0B & 0b11111000 | 0x03;        //Timer 0 Teiler 64
  //TCCR3B = TCCR3B & 0b11111000 | 0x01;        //Timer 3 Teiler 1
  //TCCR1B = TCCR1B & 0b11111000 | 0x02;        //Timer 1 Teiler 8
  
  //Input Pins Raspberry Pi
  pinMode(IN_LED_RED,INPUT);
  pinMode(IN_LED_GREEN,INPUT);
  pinMode(IN_SUMMER,INPUT);
  
  pinMode(DRIVE_UP,INPUT);
  pinMode(DRIVE_DOWN,INPUT);
  
  pinMode(SCHERE_Pin2,INPUT);
  pinMode(SCHERE_Pin4,INPUT);
  
  digitalWrite(IN_LED_RED,LOW);
  digitalWrite(IN_LED_GREEN,LOW);
  digitalWrite(IN_SUMMER,LOW);
  
  digitalWrite(DRIVE_DOWN,LOW);
  digitalWrite(DRIVE_UP,LOW);
  
  digitalWrite(SCHERE_Pin2,LOW);
  digitalWrite(SCHERE_Pin4,LOW);
  
  //Output Pin für Raspberry Pi 
  pinMode(SCHERE_Pin3,OUTPUT);
  digitalWrite(SCHERE_Pin3,LOW);
  pinMode(SCHERE_Pin5,OUTPUT);
  digitalWrite(SCHERE_Pin5,LOW); 

  //Input für BT Connection
  // pinMode(Spare1_Pin5,INPUT);

  //Dabble.begin(9600);  

}
