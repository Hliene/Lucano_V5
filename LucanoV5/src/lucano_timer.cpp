#include "..\lib\lucano_timer.h"
#include "..\lib\lucano_lidar.h"

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//Variablen für den Lidar1 um Aeste zu erkennen 
int distance = 0;
int strength = 0;
int branch_thinkness = 0;
int branch_detactet = 0;
int branch_distance = 0;


/*****************************************************************************
 * Function name:     init_ISR_2
 * 
 * Descriptions:      Funktion zur Initalisierung des Timer 2 Interrupts
 *                    Timer wird auf 1ms gesetzt                
 * 
 *****************************************************************************/
void init_ISR_2(void){

  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B

  TCCR2A=(1<<WGM01);    //Set the CTC mode   
  OCR2A = 500;          //Value for ORC0A for 1ms
 
  TIMSK2|=(1<<OCIE0A);   //Set the interrupt request
  sei(); //Enable interrupt
 
  TCCR2B|=(1<<CS12);    //Set the prescale 1/64 clock
  TCCR2B|=(1<<CS10);

  /*
  TCCR2A = (1<<WGM01);                // CTC Modus
  TCCR2B = (1<<CS10) | (1<<CS12);;    // Timer mode with 1024 prescler
  OCR2A = 249;                        // Wert für das match Register =>125 ist ca. alle 1ms  
  TIMSK2 |= (1<<OCIE2A);              // Compare Interrupt erlauben  
  sei();*/
}


/*****************************************************************************
 * Function name:     ISR (TIMER2_COMPA_vect)
 * 
 * Descriptions:      Interrupt zum auslesen der Lidar-Sensors zur Asterkennung 
 *                    
 * 
 *****************************************************************************/
ISR (TIMER2_COMPA_vect)
{
//getTF_High_Data(&distance,&strength);



}

